# U-TTL
U-TTL is an application for Linux. Use with an usb-ttl (usart) adapter. 

Create build/ dir:
```sh
mkdir build/
```

The first thing you need to do:
```sh
meson setup build/ #setup meson in build/
```

Then go to the build directory:
```sh
cd build/
```
Finally compile it:
```sh
ninja
```

**OR**

```sh
meson compile
```

For run type:
```sh
./u-ttl <baud_rate> /dev/<your_device>
```
