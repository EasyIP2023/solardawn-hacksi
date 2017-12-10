# solardawn first proto

# Depreciated!!!!
This Repo will no longer be maintained it was used for hackSI a hackathon event hosted at SIU, but will no longer be in use. It currently acts as a record of the project progress.

Open Source Project to allow people to buy and sell electricity to each other. This adaptation is designed to work with the raspberry pi zero. It follows a basic client server model, but for future use we plan on making it follow a peer-to-peer model, like [gtk-gnutella](https://github.com/gtk-gnutella/gtk-gnutella).
Website and GoFundme

* [Project Solar Dawn](https://project-solardawn.com)
* [Go fund Me](https://www.gofundme.com/project-solardawn)

## Installation
Are solar panel outputs about 1.2 A, so to have a surplus of power going into the grid we are using the lite version of raspbian [Raspbian Stretch Lite](https://www.raspberrypi.org/downloads/raspbian/). Because of it there are dependecies that need to be installed for the software to work.

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
