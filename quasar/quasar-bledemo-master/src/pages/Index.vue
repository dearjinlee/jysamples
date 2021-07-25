<template>
  <q-page class="flex flex-center">
    <q-list bordered separator>
      <q-item v-for="(device, index) in devices" :key="index" clickable v-ripple>
        <q-item-section>{{device.name}} : {{device.id}}</q-item-section>
      </q-item>
    </q-list>

    <input v-model="message" placeholder="New Todo">
    <button @click="$pouch.post({message: message},{},'todos');message=''">Save Todo</button>
    <div v-for="(todo, index) in todos" :key="index">
      <input v-model="todo.message" @change="$pouch.put(todo,{},'todos')">
      <button @click="$pouch.remove(todo,{},'todos')">Remove</button>
    </div>
  </q-page>
</template>

<script>
export default {
  name: 'PageIndex',
  data() {
    return {
      devices: [],
      message: '',
    }
  },
  // VuePouch adds a `pouch` config option to all components.
  pouch: {
    // The simplest usage. queries all documents from the "todos" pouch database and assigns them to the "todos" vue property.
    todos: {/*empty selector*/}
  },
  mounted() {
    ble.startScan([], (device) => {
        console.log(JSON.stringify(device))
        this.devices.push(device)
    }, () => {
      console.error('failed to scan')
    });

    setTimeout(ble.stopScan,
        5000,
        () => { console.log("Scan complete") },
        () => { console.log("stopScan failed") }
    );
  }
}
</script>
