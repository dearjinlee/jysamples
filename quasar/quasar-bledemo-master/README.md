# BLE Demo (ble-demo)

BLE Demo

## Install the dependencies
```bash
npm install
```

### Start the app in development mode (hot-code reloading, error reporting, etc.)
```bash
quasar dev
quasar dev -m cordova -T android
```

### Lint the files
```bash
npm run lint
```

### Build the app for production
```bash
quasar build
quasar clean
quasar build -m cordova -T android
jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore my-release-key.keystore C:\Users\sungy\workspace\quasar\BLE-Demo\dist\cordova\android\apk\release\bledemo.apk alias_name
```
password : malboro88
### BLE format

No	내용	상세내용
byte1	0x7E	Start byte(고정값)
byte2	현재온도	데이터 전송 시 +90값 전송(-85도이면 5전송)
byte3	모드	0 : "-"
		1 : 화이자
		2 : 모더나
		3 : 아스트라제네카
		4 : 얀센
byte4	고내온도	데이터 전송 시 +90값 전송(-85도이면 5전송)
byte5	잠금상태	0 : Unlock
1 : Lock
byte6	알람상태	0 : Normal
1 : Alarm
byte7	Checksum	byte1~6까지 Sum한 1byte


