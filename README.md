# fuzz-me-hard
fuzz-me-hard is a Dumb (dumbest) File Format Fuzzer program written in c++17. It accepts a binary which accepts an image file as an argument and one sample argument. Mutates the argument creates new arguments, gives them to the binary and tries to cause an error.

## Compile

```bash
g++ -std=c++17 src/*.cpp -o fuzz_me_hard
```

## Usage

```bash
./fuzz_me_hard -w <work_directory> -b <binary_path> -f <sample_argument_path>
```
example

```bash
sudo ./fuzz_me_hard -w ~/workdir/ -b ~/image_process/a.out -f ~/image_process/small_city.pgm
```

Example output:

```bash
Process 78296 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-5-0.pgm)
Process 78303 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-5-1.pgm)
Process 78306 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-5-2.pgm)
Process 78308 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-5-3.pgm)
Process 78311 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-5-4.pgm)
Process 78324 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-5-5.pgm)
Process 78326 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-5-6.pgm)
Process 78328 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-5-7.pgm)
Process 78332 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-5-8.pgm)
Process 78334 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-6-0.pgm)
Process 78336 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-6-1.pgm)
Process 78338 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-6-2.pgm)
Process 78340 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-6-3.pgm)
Process 78342 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-6-4.pgm)
Process 78344 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-6-5.pgm)
Process 78346 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-6-6.pgm)
Process 78348 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-6-7.pgm)
Process 78350 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-6-8.pgm)
Process 78352 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-7-0.pgm)
Process 78354 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-7-1.pgm)
Process 78356 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-7-2.pgm)
Process 78358 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-7-3.pgm)
Process 78360 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-7-4.pgm)
Process 78362 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-7-5.pgm)
Process 78364 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-7-6.pgm)
Process 78366 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-7-7.pgm)
Process 78368 killed: signal 6 - core dumped  (filename: /home/kaancaglan/development/workdir/temp/small_city-7-8.pgm)
90 mutation executed, current crash count: 27
180 mutation executed, current crash count: 27
270 mutation executed, current crash count: 27
360 mutation executed, current crash count: 27
450 mutation executed, current crash count: 27
540 mutation executed, current crash count: 27
630 mutation executed, current crash count: 27
720 mutation executed, current crash count: 27
810 mutation executed, current crash count: 27
900 mutation executed, current crash count: 27
990 mutation executed, current crash count: 27
1080 mutation executed, current crash count: 27
1170 mutation executed, current crash count: 27
1260 mutation executed, current crash count: 27
1350 mutation executed, current crash count: 27
1440 mutation executed, current crash count: 27
1530 mutation executed, current crash count: 27
1620 mutation executed, current crash count: 27

```
