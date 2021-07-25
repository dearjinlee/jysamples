const routes = [
  {
    path: '/',
    component: () => import('layouts/MainLayout.vue'),
    children: [
      { path: '', redirect: '/devices' },
      { path: '/devices',
        component: {
          render (c) { return c('router-view') }
        },
        children: [
          { path: '', meta: { label: 'Devices'}, component: () => import('pages/Devices.vue') },
          { path: ':id', meta: { label: 'Device Info'}, component: () => import('pages/DeviceInfo.vue')}
        ] 
      },
      { path: '/logs', meta: { label: 'Logs'}, component: () => import('pages/Logs.vue') },
      { path: '/settings',  meta: { label: 'Settings'}, component: () => import('pages/BleList.vue') }
    ]
  },

  // Always leave this as last one,
  // but you can also remove it
  {
    path: '*',
    component: () => import('pages/Error404.vue')
  }
]

export default routes
