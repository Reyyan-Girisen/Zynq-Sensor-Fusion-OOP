# MPU6050 I2C Pinleri (Arduino Header: SCL ve SDA)
set_property -dict { PACKAGE_PIN P16   IOSTANDARD LVCMOS33 } [get_ports { IIC_0_0_scl_io }];
set_property -dict { PACKAGE_PIN P15   IOSTANDARD LVCMOS33 } [get_ports { IIC_0_0_sda_io }];

# HX711 GPIO Pinleri (Arduino Header: D0 ve D1)
set_property -dict { PACKAGE_PIN T14   IOSTANDARD LVCMOS33 } [get_ports { GPIO_0_0_tri_io[0] }];
set_property -dict { PACKAGE_PIN U12   IOSTANDARD LVCMOS33 } [get_ports { GPIO_0_0_tri_io[1] }];