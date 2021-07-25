<template>
  <q-page class="flex flex-center">
    <q-list bordered separator>
      <q-item v-for="device in devices" :key="device.id" :to="'/devices/' + device.id.replaceAll(':', '-')" clickable v-ripple>
        <q-item-section avatar>
          <q-icon color="negative" name="settings_remote" />
        </q-item-section>
        <q-item-section>
          <q-item-label>{{device.id}}</q-item-label>
          <q-item-label>
            <q-icon v-show="device.created < allowedTime" color="negative" name="pending_actions" />{{getTimeStr(device.created)}},
            {{getModeName(device.mode)}}
            <q-icon color="primary" :name="device.lock ? 'lock': 'lock_open'" />
            <q-icon v-show="device.alarm" color="negative" name="warning" />
          </q-item-label>
        </q-item-section>
        <q-item-section side top>
          <q-icon color="primary" name="thermostat" /> {{device.currTemp}}&#176;C
        </q-item-section>          
        <q-item-section side top>
          <q-icon color="secondary" name="thermostat" /> {{device.inTemp}}&#176;C
        </q-item-section>          
      </q-item>
    </q-list>
  </q-page>
</template>

<script>
import { date } from 'quasar'

export default {
  name: 'PageDevices',
  data() {
    return {
      timestamp: 0
    }
  },
  computed: {
    devices() {
      return this.$store.getters['bledemo/getDevices']
    },
    allowedTime() {
      const timestamp = this.timestamp - 10*1000
      console.log('allowedTime', timestamp)
      return timestamp
    }
  },
  mounted() {
    setInterval(this.getNow, 1000)
  },
  methods: {
    getNow() {
      //console.log(Date.now())
      this.timestamp = Date.now()
    },
    getTimeStr(timeStamp) {
      let formattedString = date.formatDate(timeStamp, 'HH:mm:ss')
      console.log(formattedString)
      return formattedString
    },
    getModeName(mode) {
      switch(mode) {
        case 1: return 'Pfizer'
        case 2: return 'Moderna'
        case 3: return 'AstraZeneca'
        case 4: return 'Jannsen'
        default: return '-'
      }
    }
  }
}
</script>
