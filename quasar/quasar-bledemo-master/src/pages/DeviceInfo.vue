<template>
  <q-page class="flex flex-center">
    <div class="row items-center" style="width:100%; margin-left:1rem;">
      <div class="col self-start">
        <q-btn color="primary" icon="mail" size="xs" rounded :label="prevDay().toLocaleDateString()" @click="changeDay(-1)"/>
      </div>
      <div class="col self-center">
        <q-item-label>{{selectedDate.toLocaleDateString()}}</q-item-label>
      </div>
      <div class="col self-end">
        <q-btn color="secondary" icon-right="mail" size="xs" rounded :label="nextDay().toLocaleDateString()" @click="changeDay(1)"/>
      </div>
    </div>
    <q-item-label>{{deviceId}}</q-item-label>
    <line-chart v-if="datacollection" :chart-data="datacollection" :options="options" :key="compositeKey"></line-chart>
  </q-page>
</template>

<script>
  import { date } from 'quasar'
  import LineChart from '../mixins/LineChart.js'

  let csvFullPath = null

  function saveBlob2File (fileName, blob) {
    var folder = cordova.file.externalRootDirectory
    console.log('folder', folder)
    window.resolveLocalFileSystemURL(folder, function (dirEntry) {
      console.log('file system open: ' + dirEntry.name)
      createFile(dirEntry, fileName, blob)
    }, onErrorLoadFs)
  }

  function createFile (dirEntry, fileName, blob) {
    // Creates a new file
    dirEntry.getFile(fileName, { create: true, exclusive: false }, function (fileEntry) {
      writeFile(fileEntry, blob)
    }, onErrorCreateFile)
  }

  function writeFile (fileEntry, dataObj) {
    // Create a FileWriter object for our FileEntry
    fileEntry.createWriter(function (fileWriter) {
      fileWriter.onwriteend = function () {
        console.log('Successful file write...')
        cordova.plugins.fileOpener2.open(
            csvFullPath,
            'text/csv',
            {
              error: (e) => { console.error(e) },
              success: () => { console.log('file opened successfully ')}
            }
        )          
      }

      fileWriter.onerror = function (error) {
        console.log('Failed file write: ' + error)
      }
      fileWriter.write(dataObj)
    })
  }

  function onErrorLoadFs (error) {
    console.log(error)
  }

  function onErrorCreateFile (error) {
    console.log(error)
  }

  export default {
    components: {
      LineChart
    },
    data () {
      return {
        temps: [],
        compositeKey: 0,
        deviceId: null,
        selectedDate: new Date(),
        datacollection: null,
        options: {
          responsive: true,
          title: {
            display: true,
            text: 'Temperatures'
          },
          scales: {
            yAxes: [{
              stacked: false,
              ticks: {
                beginAtZero: false,
                stepSize: 10,
                min: -100,
                max: 30,                  
              },
              gridLines: {
                display: true,
                drawBorder: false,
              }
            }]
          },
        },
      }
    },
    mounted () {
      console.log('device id', this.$route.params.id)
      this.deviceId = this.$route.params.id.replaceAll('-', ':')
      // this.fillData('04:78:63:D1:0D:E8')
      this.fillData(this.deviceId)
    },
    watch: {
      selectedDate() {
        this.fillData(this.deviceId)
        this.compositeKey += 1
      }
    },
    methods: {
      nextDay() {
        return date.addToDate(this.selectedDate, { days: 1 })
      },
      prevDay() {
        return date.addToDate(this.selectedDate, { days: -1 })
      },
      changeDay(days) {
        this.selectedDate = date.addToDate(this.selectedDate, { days })
      },
      async exportCSV() {
        let items = await this.fetchDataAll(deviceId)
        items = items.map(v => {
          v.created = new Date(v.created).toISOString()
          return v
        })
        const replacer = (key, value) => value === null ? '' : value
        const header = Object.keys(items[0])
        const csv = [
          header.join(','), // header row first
          ...items.map(row => header.map(fieldName => JSON.stringify(row[fieldName], replacer)).join(','))
        ].join('\r\n')

        const blob = new Blob([csv])
        const fileName = this.deviceId.replaceAll(':', '') + '-' + Date.now() + '.csv'
        csvFullPath = cordova.file.externalRootDirectory + fileName
        saveBlob2File(fileName, blob)
        console.log('filename:', fileName, 'fullPath:', csvFullPath)
      },
      async fetchData(deviceId) {
        console.log('start fetchData')
        const docs = await this.$pouch.find({
          selector: {deviceId},
          fields: ['created', 'currTemp', 'inTemp'],
          // sort: ['created']
        }, 'temperatures')
        console.log('fetched data', docs.docs)
        return docs.docs
        // this.temps = docs.docs
      },
      async fetchDataAll(deviceId) {
        console.log('start fetchDataAll')
        const docs = await this.$pouch.find({
          selector: {deviceId},
          fields: ['deviceId', 'created', 'currTemp', 'inTemp', 'lock', 'alarm', 'mode'],          
          // sort: ['created']
        }, 'temperatures')
        console.log('fetched data', docs.docs)
        return docs.docs
        // this.temps = docs.docs
      },
      getHourlyChartData(yyyy, mm, dd) {
        const range = this.range(0, 24, 1)
        const dayTemps = range.map(hour => {
          let currTemp = null
          let inTemp = null
          let i = 0
          const refHour = new Date(yyyy, mm, dd, hour)
          this.temps.map(v => {
            const minDate = refHour.setMinutes(0, 0, 0)
            const maxDate = refHour.setMinutes(59, 59, 99)
            const vDate = v.created
            // console.log(minDate, maxDate, vDate, new Date(minDate).toString(), new Date(maxDate).toString(), new Date(vDate).toString())            
            if (vDate >= minDate && vDate <= maxDate) {
              currTemp += v.currTemp
              inTemp += v.inTemp
              i += 1
            }
          })
          return i ? [Math.round(currTemp/i), Math.round(inTemp/i)] : [null, null]
        })
        // console.log('dayTemps', dayTemps)
        return dayTemps
      },
      range (start, stop, step) {
        return Array.from(
          { length: (stop - start) / step + 1}, 
          (_, i) => start + (i * step)
        )
      },
      async fillData (deviceId) {
        this.temps = await this.fetchData(deviceId)
        const dayTemps = this.getHourlyChartData(this.selectedDate.getFullYear(), this.selectedDate.getMonth(), this.selectedDate.getDate()) // month는 1부터 시작
        // const dayTemps = [null, null, ...Array.from({length: 23}, (_, i) => i - 70)]
        console.log('dayTemps', dayTemps)
        this.datacollection = {
          labels: this.range(0, 24, 1),
          datasets: [
            {
              label: '현재온도',
              fill: false,
              backgroundColor: '#f87979',
              borderColor: '#f87979',
              data: dayTemps.map(v => v[0])
            },
            {
              label: '설정온도',
              fill: false,
              backgroundColor: 'skyblue',
              borderColor: 'skyblue',
              data: dayTemps.map(v => v[1])
            }
          ]
        }
        console.log(this.datacollection)
      },
    }
  }
</script>

<style>
  .small {
    max-width: 600px;
    margin:  150px auto;
  }
</style>