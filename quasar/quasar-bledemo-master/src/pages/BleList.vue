<template>
  <q-page class="flex flex-center">
    <div class="row items-center" style="width:100%; margin-left:1rem;">
      <div class="col self-start">
        <q-btn color="warning" label="Reset All" @click="resetAll"/>        
      </div>
      <div class="col self-center">
        <q-btn color="primary" :label="isScanning ? 'Stop SCAN': 'Start SCAN'" @click="toggleScan"/>
      </div>
      <div class="col self-end">
        <q-btn color="warning" label="Exit" @click="exitApp"/>
      </div>
    </div>    
    <q-list bordered separator>
      <q-item v-for="device in devices" :key="device.id" clickable v-ripple>
        <q-item-section>{{device.name}} : {{device.id}}</q-item-section>
        <q-item-section side top>
          <q-toggle color="red" v-model="device.connected" val="picture" 
            @input="device.connected ? connect(device): disconnect(device)"
          />
        </q-item-section>
      </q-item>
    </q-list>
  </q-page>
</template>

<script>
export default {
  name: 'PageBleList',
  data() {
    return {
      devices: [],
      message: '',
      isScanning: false,
      disconnectedAll: false
    }
  },
  mounted() {
    console.log('mounted')
    this.getBondedDevices()
  },
  methods: {
    exitApp() {
      this.disconnectAll()
      setTimeout(() => {
        this.disconnectedAll && navigator.app.exitApp()
      }, 2000)
    },
    getBondedDevices() {
      ble.bondedDevices(
        v => { console.log('bonded devices', v)}, 
        () => { console.log('failed to get bonded devices')}
      )
    },
    async createIndex() {
      console.log('create Index')
      await this.$pouch.createIndex({
          index: {
            fields: ['deviceId', 'created']
          }
      }, 'temperatures')
    },
    resetAll() {
      console.log('resetAll')
      this.devices = []      
      this.disconnectAll()
      this.$pouch.destroy('temperatures')      
      this.$pouch.destroy('bledemo')
      this.$store.commit('bledemo/setDevices', [])
      this.createIndex()
    },
    startScan() {
      console.log('startScan')
      this.isScanning = true
      this.devices = []
      ble.startScan([], (device) => {
          console.log(JSON.stringify(device))
          // const adData = new Uint8Array(device.advertising)
          // console.log('adData', adData)
          device.connected = false
          this.devices.push(device)
      }, () => {
        console.error('failed to scan')
      })

      setTimeout(ble.stopScan,
        5000,
        () => { 
          console.log("stopScan complete") 
          this.isScanning = false
        },
        () => { 
          console.log("stopScan failed") 
          this.isScanning = false
        }
      );
    },
    toggleScan() {
      console.log('toggleScan')
      this.isScanning ? ble.stopScan(): this.startScan()
    },
    connect(device) {
      console.log(device)
      ble.connect(
        device.id, 
        (v) => {
          console.log('connected', v)
          this.addDevice(device)
        }, 
        (e) => {
          console.error('connection error', e)
          device.connected = false
        }
      )          
    },
    stopNotification(deviceId) {
      const serviceId = '0000e0ff-3c17-d293-8e48-14fe2e4da212'
      const characteristicId = '0000ffe2-0000-1000-8000-00805f9b34fb'

      const onFailure = (e) => {
        console.warn(deviceId, e)
      }
      const onData = (buffer) => {
          const tempItem = this.decodeRawData(buffer, deviceId)
          if (!tempItem) return
          console.log('tempItem', tempItem)
          this.$pouch.post(tempItem, {}, 'temperatures')
          this.$store.commit('bledemo/updateDevice', tempItem)
      }
      console.log('start subscribe', deviceId)
      ble.stopNotification(deviceId, serviceId, characteristicId, onData, onFailure)
     },
    async disconnectAll() {
      const devices = this.$store.getters['bledemo/getDevices']
      let cnt = devices.length
      devices.map(device => {
        ble.disconnect(
          device.id, 
          () => { 
            console.log(device.id + ' disconnected')
            cnt -= 1
            this.disconnectedAll = !cnt
          }, 
          () => { 
            console.error(device.id + ' disconnection failed')
            cnt -= 1
            this.disconnectedAll = !cnt
          }
        )
      })
    },    
    disconnect(device) {
      console.log('disconnect device', device)
      ble.disconnect(
        device.id, 
        () => { console.log(device.id + ' disconnected')}, 
        () => { console.error(device.id + ' disconnection failed')}
      )
    },
    addDevice(device) {
      const deviceItem = {
        _id: device.id,
        name: device.name,
        created: Date.now(),
        temperature: -75.5
      }
      console.log('addDevice', device)
      this.$pouch.put(deviceItem)
      deviceItem.id = device.id
      this.subscribe(device.id)
      this.$store.commit('bledemo/addDevice', device)
    },
    decodeRawData(buffer, deviceId) {
      const data = new Uint8Array(buffer)
      console.log('onData', data)
      if (!data || data.length < 7) {
        console.warn('invalid data length')
        return null
      }
      if (data[0] !== 0x7E) {
        console.warn('1st packet should start with 0x7E')
        return null
      }
      return {
        created: Date.now(),
        deviceId,
        currTemp: data[1] - 90,
        mode: data[2],
        inTemp: data[3] - 90,
        lock: data[4],
        alarm: data[5]
      }
    },
    async subscribe(deviceId) {
      const serviceId = '0000e0ff-3c17-d293-8e48-14fe2e4da212'
      const characteristicId = '0000ffe2-0000-1000-8000-00805f9b34fb'

      const onFailure = (e) => {
        console.warn(deviceId, e)
      }
      const onData = (buffer) => {
          const tempItem = this.decodeRawData(buffer, deviceId)
          if (!tempItem) return
          console.log('tempItem', tempItem)
          this.$pouch.post(tempItem, {}, 'temperatures')
          this.$store.commit('bledemo/updateDevice', tempItem)
      }
      console.log('start subscribe', deviceId)
      ble.startNotification(deviceId, serviceId, characteristicId, onData, onFailure)
    },
  },
}
</script>
