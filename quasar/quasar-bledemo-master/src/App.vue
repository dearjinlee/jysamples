<template>
  <div id="q-app">
    <router-view />
  </div>
</template>
<script>
export default {
  name: 'App',
  data() {
    return {

    }
  },
  created() {
    window.plugins.insomnia.keepAwake()
    this.createIndex()
    ble.setPin(
        '234567',
        (v) => {
          console.log('pin success', v)
          this.autoConnectAll()
        }, 
        (e) => {
          console.error('pin error', e)
        }
      )          
  },
  beforeDestroy() {
    this.disconnectAll()
  },
  methods: {
    async createIndex() {
      console.log('create Index')
      await this.$pouch.createIndex({
          index: {
            fields: ['deviceId', 'created']
          }
      }, 'temperatures')
    },
    async disconnectAll() {
      const devices = this.$store.getters['bledemo/getDevices']
      devices.map(device => {
        ble.disconnect(
          device.id, 
          () => { console.log('disconnected')}, 
          () => { console.error('disconnection failed')}
        )
      })
    },
    async autoConnectAll() {
      const docs = await this.$pouch.allDocs()
      const devices = docs.rows.map(v => {
        const device = v.doc
        device.id = v.doc._id
        ble.autoConnect(
          device.id, 
          () => { 
            console.info(`${device.id} connected`)
            //this.startReading(device.id)
            this.subscribe(device.id)
          }, 
          () => { console.info(`${device.id} disconnected`)}
        )
        return v.doc
      })
      console.log('autoConnectAll', devices)
      this.$store.commit('bledemo/setDevices', devices)
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
    async startReading(deviceId) {
      setTimeout(() => {
        this.readTemperature(deviceId)
        this.startReading(deviceId)
      }, 15*1000) // 15s
    },
    async readTemperature(deviceId) {
      const serviceId = '00001800-0000-1000-8000-00805f9b34fb'
      const characteristicId = '00002a01-0000-1000-8000-00805f9b34fb'
      ble.read(deviceId, serviceId, characteristicId,
        (data) => {
            console.log(JSON.stringify(data))
            const temperature = -80.45 // to get correct device
            const tempItem = {
              created : Date.now(),
              deviceId,
              temperature
            }
            this.$pouch.post(tempItem, {}, 'temperatures')
            this.$store.commit('bledemo/updateDevice', tempItem)
        },
        () => {
            console.warn('Failed to read temperature from ' + deviceId)
        }
      )
    }
  }
}
</script>
