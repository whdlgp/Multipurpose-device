# Multipurpose-device

## A brief introduction
![](http://i.imgur.com/ej1iP6O.jpg)

This project deals with devices that utilize the Atmega128 with a few simple features.  
It is designed to allow several tasks to work together asynchronously, allowing each function to be executed simply and periodically.

![](http://i.imgur.com/q5PVLTV.png)  
(Look only at the flow because it is the diagram that I made freely.)  

```cpp
	while(1)
    {
		sensor_read_process(10000);//10ms
		
		//print mode number to LED
		gpio_write(D, ~((1 << sensor->mode) << 4) & 0xf0);
		
		//select mode
		switch(sensor->mode)
		{
			case 0:
			//bit calculator
			bit_calculator_process(50000); //50ms
			break;
			
			case 1:
			//stopwatch
			stopwatch_process(50000); //50ms
			break;
			
			case 2:
			//count the size of bit
			allyouneedisbit_process(50000); //50ms
			break;
			
			default:
			test_process(100000); //100ms
			break;
		}
		
		lcd_process(200000); //200ms
	}
```

Each mode is selected by a potentiometer for selection.  
In practice, three tasks are operated asynchronously, part of which reads the sensor (keypad, etc.), selected mode, and CLCD.  

## Printed LCD Image

### HEX to BIN calculator
![](http://i.imgur.com/WYXYS2g.jpg)  

### Simple Stopwatch
![](http://i.imgur.com/8CH75A8.jpg)

### require bits calculator
![](http://i.imgur.com/4vqaVwI.jpg)

