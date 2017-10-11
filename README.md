# solardawn
Open Source Project to allow people to buy and sell electricity to each other. This adaptation is designed to work with the raspberry pi zero.

Website and GoFundme
* [Project Solar Dawn](https://project-solardawn.com)
* [Go fund Me](https://www.gofundme.com/project-solardawn)

## Installation
Are solar panel give produced about 1.2 A, so to conserve power we are using the lite version [Raspbian Stretch Lite](https://www.raspberrypi.org/downloads/raspbian/). Because of it there are dependecies that need to be installed for the software to work.

```
sudo apt install libglib2.0-dev \
sudo apt install libgtk-3-dev   \
sudo apt install libxml2-utils  \
sudo apt install xorg           \
sudo apt install openbox        \
sudo reboot
```

After installing dependecies.
```bash
cd src/
```
```bash
make
```
```bash
./solardawn
```
