Simulation Setting Start on Desktop (Unreal, Airsim, Ardupilot_gazebo plugin)
===
### 0. Simulation on Desktop
- 개념도

![제목 없음](https://user-images.githubusercontent.com/108650199/178150729-f5507029-64a9-4391-96a4-87172488e1ea.png)

![SITL](https://user-images.githubusercontent.com/108650199/178149144-f385be5a-59b3-4e78-b5d3-712843945bcb.png)

- MAVLink : 드론과 자비에 통신을 위한 메시징 프로토콜로 Ardupilot과 Companion computer간에 데이터와 커맨드를 전송하는데 가장 일반적으로 사용
- Ardupilot : 아두파일럿이란 아두이노+Autopilot의 줄임말으로, 픽스호크 하드웨어를 위한 펌웨어
  - 다양한 하드웨어 환경의 Vehicle에 탑재될 수 있는 오픈 소스 autopilot system
- ArduPilot은 기본 펌웨어 시뮬레이터인 SITL(software in the loop)을 사용할 수 있으며, 그 외에도 gazebo, airsim 등이 있음

### 1. Build Unreal Engine
+ Epic Games에 등록 후 Github계정을 연결
+ 참고 : https://www.unrealengine.com/en-US/blog/updated-authentication-process-for-connecting-epic-github-accounts

### 2. Build Unreal Engine
```
git clone -b 4.27 git@github.com:EpicGames/UnrealEngine.git
```
> Trouble Shooting
```
Error : Permission denied (publickey)
```
+ 위 에러 메세지는 ssh key가 github에 등록되지 않아 발생하는 문제


> 해결 : ssh key를 local에 생성한 뒤 등록
```
ssh-keygen -t rsa -C "MY GITHUB EMAIL"
cat ~/.ssh/id_rsa.pub
```
+ 마지막 코드 실행시 나오는 것 복사해서 git hub ssh 키 추가하면 Permission OK
```
cd UnrealEngine
./Setup.sh
./GenerateProjectFiles.sh
make
```

### 3. Build Airsim
```
git clone https://github.com/Microsoft/AirSim.git
cd AirSim
./setup.sh
./build.sh
```

### 4. Start
```
./Engine/Binaries/Linux/UE4Editor
```
+ Choose 
  + AirSim/Unreal/Environments/Blocks
> Trouble Shooting 
+ engine modules are out of date and cannot be compiled while the engine is running Please build through your IDE
> 해결
```
Engine/Source/Developer/DesktopPlatform/Private/DesktopPlatformBase.cpp 
Look for this line : Arguments += " -Progress -NoEngineChanges -NoHotReloadFromIDE"; → Arguments += " -Progress";
```
+ Then re-compile your engine launch your project and accept the rebuild 
```
cd UnrealEngine
./Setup.sh
./GenerateProjectFiles.sh
make
```
![Screenshot from 2022-07-07 19-06-28](https://user-images.githubusercontent.com/108650199/177748927-13d5e6c5-30c6-465e-b576-b65aba09a65a.png)

---
## Trouble Shooting 
### 5. Ardupilot gazebo plugin

```
git clone https://github.com/SwiftGust/ardupilot_gazebo
cd ardupilot_gazebo
mkdir build
cd build
cmake ..
make -j4
sudo make install

sudo gedit ~/.bashrc
```
+ 추가 > 없앴음
```
source /usr/share/gazebo/setup.sh

export GAZEBO_MODEL_PATH=~/ardupilot_gazebo/models:${GAZEBO_MODEL_PATH}
export GAZEBO_MODEL_PATH=~/ardupilot_gazebo/models_gazebo:${GAZEBO_MODEL_PATH}
export GAZEBO_RESOURCE_PATH=~/ardupilot_gazebo/worlds:${GAZEBO_RESOURCE_PATH}
export GAZEBO_PLUGIN_PATH=~/ardupilot_gazebo/build:${GAZEBO_PLUGIN_PATH}
````
+ 공식 홈 참고 : https://ardupilot.org/dev/docs/using-gazebo-simulator-with-sitl.html 

```
git clone https://github.com/ArduPilot/ardupilot.git
cd ardupilot
git submodule update --init --recursive
```
+ Trouble Shooting 
```
git submodule update --init --recursive
```
```
Waf: Leaving directory `/home/dam/ardupilot/build/sitl'
Build failed
 -> task in 'objs/AP_GPS' failed (exit status 1): 
	{task 139997242944752: cxx AP_GPS.cpp -> AP_GPS.cpp.0.o}
 (run with -v to display more information)
SIM_VEHICLE: Build failed
SIM_VEHICLE: Killing tasks
```
+ 이유
	+ The plugin we will be using works with gazebo versions 7 to 9. We recommend gazebo9 as the new development will append on this version.
	+ But my gazebo version is 11
	+ So, Gazebo11 REMOVE
	```
	sudo apt-get remove gazebo11
	sudo apt-get -y purge gazebo11
	sudo apt-get -y autoremove gazebo11
	```
	+ Install Gazebo9
	```
	sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
	cat /etc/apt/sources.list.d/gazebo-stable.list.
	deb http://packages.osrfoundation.org/gazebo/ubuntu-stable xenial main
	wget https://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
	sudo apt-get update
	sudo apt-get install gazebo9
	sudo apt-get install libgazebo9-dev
	```
---

### 6. Install the ArduPilot (ArduPilot)
> Reference : LMJ NAS
```
sudo apt-get update
sudo apt-get install git
sudo apt-get install gitk git-gui
git clone https://github.com/ArduPilot/ardupilot
cd ardupilot
git submodule update --init --recursive
Tools/environment_install/install-prereqs-ubuntu.sh -y
. ~/.profile
```

### 7. Plugin installation (ArduPilot)
> Reference : LMJ NAS
```
git clone https://github.com/khancyr/ardupilot_gazebo
cd ardupilot_gazebo
mkdir build
cd build
cmake ..
make -j4
sudo make install
```
 
### 8. start the simulator (ArduPilot)
> Reference : LMJ NAS
```
gazebo --verbose worlds/iris_arducopter_runway.world
cd ~/ardupilot/ArduCopter
../Tools/autotest/sim_vehicle.py -f gazebo-iris --console --map
```

> Trouble Shooting : Gazebo runway.world Error

![err](https://user-images.githubusercontent.com/108650199/177949657-1dd059d2-04d7-436e-96c7-d520b5aed13a.png)

> 해결 
+ Reference : https://intrepidgeeks.com/tutorial/cannot-open-shared-object-file-no-such-file-or-directory
	+ so 파일이란 shared object 파일로 특정한 기능을 구현해 놓은 파일로 so 파일에 구현된 기능이 필요할 때 그 파일을 찾다가 없어서 에러가 나는 것으로 경로를 설정해주면 해결
	+ 이외에 so 파일을 찾는 경로 설정은 아래와 같다
		+ 1. system default 경로
		+ 2. LD_LIBRARY_PATH
		+ 3. binary code 에 hard-coding 된 경로

```
eb

export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

sb
```

![ardu gaze](https://user-images.githubusercontent.com/108650199/178189355-8fb63eab-5b8b-4296-b3a3-e543b9366fcb.png)


+ Reference : https://www.youtube.com/watch?v=m7hPyJJmWmU 
	+ 드론 동작 확인

![ardu gaze up](https://user-images.githubusercontent.com/108650199/178189364-8bf5883e-64ea-4e39-a381-9ac8f22a5244.png)


### 9. Qgroundcontrol 
```
sudo usermod -a -G dialout $USER
sudo apt-get remove modemmanager -y
sudo apt install gstreamer1.0-plugins-bad gstreamer1.0-libav gstreamer1.0-gl -y
sudo apt install libqt5gui5 -y
```
+ logout (ctal+alt+del) & login
+ Download QGroundControl.Appimage
+ Install
```
cd Downloads/
chmod +x ./QGroundControl.AppImage
./QGroundControl.AppImage
```
![Screenshot from 2022-07-08 14-08-54](https://user-images.githubusercontent.com/108650199/177943264-50fe9d09-def4-4cfb-b5f6-5cdb99d51d90.png)
