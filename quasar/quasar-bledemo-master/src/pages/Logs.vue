<template>
  <q-page class="flex flex-center">
    <q-list bordered separator>
      <q-item v-for="device in devices" :key="device.id" clickable v-ripple>
        <q-item-section>{{device.name}} : {{device.id}}</q-item-section>
        <q-item-section side>
          <button @click="exportCSV(device.id)">Export CSV</button>
        </q-item-section>
      </q-item>
    </q-list>
  </q-page>
</template>

<script>

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
  name: 'PageLogs',
  data() {
    return {
    }
  },
  computed: {
    devices() {
      return this.$store.getters['bledemo/getDevices']
    }
  },
  methods: {
  },
  methods: {
    async exportCSV(deviceId) {
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
      const fileName = deviceId.replaceAll(':', '') + '-' + Date.now() + '.csv'
      csvFullPath = cordova.file.externalRootDirectory + fileName
      saveBlob2File(fileName, blob)
      console.log('filename:', fileName, 'fullPath:', csvFullPath)
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
    }
  }
}
</script>
