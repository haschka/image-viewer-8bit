# image-viewer-8bit
view bytes as images - an 8bit raw image viewer
please see license below before considering using this tool:

This allows you to watch 8 bit images on your computer.

* compilation:

In order to compile and run this software you need to have the sdl2 library
and its development headers ( i.e. dev packages ) installed. 
```
gcc -O2 -march=native `sdl2-config --cflags` 8bit_viewer.c -c -o 8bit_viewer.o`
gcc 8bit_viewer.o `sdl2-config --libs` -o 8bit_viewer
```

* usage:

8 bit images can be obtained by using convert, which is part
of imagemagick for instance,

`convert inputfile.png -depth 8 pgm:- | tail -c 256000 > output.raw`

where 256000 is the size of the image (with by hight) 256000 is in this case
for a 640x400 image, you have to change this value according to your needs.

you can now view files like:
```
./8bit_viewer image.raw 640 400
```
where 640 by 400 is your image size.

For fun you can as 8 bit is just the size of a byte watch any file on your
system as an 8 bit image.

i.e. if you want to see the first 120000 bytes of your harddrive you could
do something like:
```
./8bit_viewer /dev/sda 200 600
```

* License
Copyright (c) 2015-2019 Thomas Haschka

This software is provided 'as-is',
without any express or implied warranty.
In no event will the authors be held
liable for any damages arising from
the use of this software.

Permission is granted to anyone to use
this software for any purpose
including commercial applications, and
to alter it and redistribute it freely,
subject to the following restrictions:

1.
The origin of this software must not
be misrepresented; you must not claim that
you wrote the original software.
If you use this software in a product,
you should cite its source.
`https://github.com/haschka/image-viewer-8bit.git`

2.
Altered source version mus plainly marked as such,
and must not be misrepresented as being the
original software.

3.
This notice may not be removed or
altered from any source distribution.
