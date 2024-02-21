# U-TTL
U-TTL is a cli application for Linux. Use with an usb-ttl (usart) adapter. 

Create build/ dir:
```sh
mkdir build/ && cd build/
```

For build type:
```sh
cmake .. && make 
```

For run type:
```sh
u-ttl <baud_rate> /dev/<your_device>
```
