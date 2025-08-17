## what left in the project 

# the cone normal when flipped (partially fixed)
# the cone angle/ width doesnt change (new / big issue that we forgot)

# cone textures 
# cylinder texture 

# valgrind

```bash 
./minirt test.rt
[1]    479327 bus error (core dumped)  ./minirt test.rt
A 	0.1				255,255,255
c 	0,0,27		0,0,-1	70
c 	0,0,40		0,0,-1	70
c 	-60,0,0		1,0,0	70
l 	0,0,5	1.0				255,255,255
l 	0,10,0		1.0				255,255,255
# cy	-10,0,0		0,1,0	2	6	0,0,255 bump=somthing.xpm
sp    0,0,0 4                        255,0,0 bump=./textures/world_map.xpm
cy	-10,-5,0		0,1,0	2	10	0,0,255 
co	10,-5,0		0,1,0	15	10	168,132,34 
pl	0,-5,0		0,1,0			255,0,255 checker=10-255,255,255-0,0,0
pl	0,-5,-10		0,0,1			255,0,255 
```