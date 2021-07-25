export function setDevices (state, devices) {
    state.devices = devices
}

export function addDevice (state, device) {
    if (state.devices) state.devices = []
    state.devices.push(device)
}

export function updateDevice (state, tempDevice) {
    state.devices = state.devices.map(v => {
        if (v.id === tempDevice.deviceId) v = {id: v.id, ...tempDevice}
        return v
    })
}
