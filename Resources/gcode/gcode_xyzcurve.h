/*
gcode_xyzcurve.h - data file containing gcode
*/

// xyzcurve test
const char PROGMEM gcode_file[] = "\
N40 G21 G90\n\
N60 F800\n\
N2000 G92 X.739 Y63.559 Z9.034\n\
N2010 G01 X.752 Y63.718 Z8.871\n\
N2020 X.771 Y63.924 Z8.662\n\
N2030 X.793 Y64.122 Z8.464\n\
N2040 X.818 Y64.313 Z8.275\n\
N2050 X.845 Y64.497 Z8.097\n\
N2060 X.874 Y64.673 Z7.928\n\
N2070 X.905 Y64.842 Z7.768\n\
N2080 X.938 Y65.005 Z7.618\n\
N2090 X.973 Y65.161 Z7.477\n\
N2100 X1.01 Y65.31 Z7.344\n\
N2110 X1.048 Y65.453 Z7.22\n\
N2120 X1.087 Y65.59 Z7.104\n\
N2130 X1.128 Y65.722 Z6.996\n\
N2140 X1.17 Y65.847 Z6.896\n\
N2150 X1.213 Y65.967 Z6.803\n\
N2160 X1.257 Y66.081 Z6.717\n\
N2170 X1.301 Y66.191 Z6.637\n\
N2180 X1.346 Y66.295 Z6.565\n\
N2190 X1.392 Y66.395 Z6.498\n\
N2200 X1.439 Y66.49 Z6.438\n\
N2210 X1.486 Y66.58 Z6.384\n\
N2220 X1.517 Y66.638 Z6.351\n\
N2230 X1.565 Y66.722 Z6.305\n\
N2240 X1.613 Y66.801 Z6.265\n\
N2250 X1.661 Y66.877 Z6.23\n\
N2260 X1.71 Y66.95 Z6.199\n\
N2270 X1.758 Y67.019 Z6.173\n\
N2280 X1.807 Y67.085 Z6.151\n\
N2290 X1.856 Y67.147 Z6.134\n\
N2300 X1.906 Y67.207 Z6.12\n\
N2310 X1.955 Y67.264 Z6.11\n\
N2320 X2.005 Y67.319 Z6.104\n\
N2330 X2.055 Y67.37 Z6.102\n\
N2340 X2.106 Y67.42 Z6.103\n\
N2350 X2.157 Y67.467 Z6.108\n\
N2360 X2.208 Y67.512 Z6.116\n\
N2370 X2.26 Y67.556 Z6.128\n\
N2380 X2.312 Y67.597 Z6.143\n\
N2390 X2.365 Y67.636 Z6.162\n\
N2400 X2.419 Y67.674 Z6.184\n\
N2410 X2.473 Y67.709 Z6.21\n\
N2420 X2.528 Y67.743 Z6.239\n\
N2430 X2.584 Y67.775 Z6.272\n\
N2440 X2.641 Y67.806 Z6.309\n\
N2450 X2.7 Y67.835 Z6.351\n\
N2460 X2.759 Y67.862 Z6.396\n\
N2470 X2.819 Y67.887 Z6.446\n\
N2480 X2.881 Y67.911 Z6.501\n\
N2490 X2.944 Y67.933 Z6.56\n\
N2500 X3.009 Y67.953 Z6.625\n\
N2510 X3.075 Y67.97 Z6.695\n\
N2520 X3.142 Y67.986 Z6.77\n\
N2530 X3.211 Y68. Z6.851\n\
N2540 X3.281 Y68.011 Z6.939\n\
N2550 X3.353 Y68.02 Z7.032\n\
N2560 X3.427 Y68.027 Z7.133\n\
N2570 X3.502 Y68.031 Z7.24\n\
N2580 X3.579 Y68.033 Z7.355\n\
N2590 X3.657 Y68.031 Z7.477\n\
N2600 X3.738 Y68.027 Z7.607\n\
N2610 X3.819 Y68.02 Z7.745\n\
N2620 X3.902 Y68.01 Z7.892\n\
N2630 X3.987 Y67.996 Z8.047\n\
N2640 X4.073 Y67.979 Z8.211\n\
N2650 X4.161 Y67.958 Z8.385\n\
N2660 X4.25 Y67.934 Z8.568\n\
N2670 X4.341 Y67.906 Z8.761\n\
N2680 X4.433 Y67.875 Z8.964\n\
N2690 X4.526 Y67.839 Z9.178\n\
N2700 X4.62 Y67.799 Z9.402\n\
N2710 X4.715 Y67.755 Z9.637\n\
N2720 X4.812 Y67.707 Z9.884\n\
N2730 X4.909 Y67.655 Z10.141\n\
N2740 X5.007 Y67.598 Z10.41";


/*
N40 G21 G90\n\
N50 G92 X0 Y0 Z0\n\
N60 F400\n\
N2140 G92 X1.17 Y65.847 Z6.896\n\
N2150 G1 X1.213 Y65.967 Z6.803\n\
N2160 X1.257 Y66.081 Z6.717\n\
N2170 X1.301 Y66.191 Z6.637\n\
N2180 X1.346 Y66.295 Z6.565\n\
N2190 X1.392 Y66.395 Z6.498\n\
N2200 X1.439 Y66.49 Z6.438\n\
N2210 X1.486 Y66.58 Z6.384\n\
N2220 X1.517 Y66.638 Z6.351\n\
N2230 X1.565 Y66.722 Z6.305\n\
N2240 X1.613 Y66.801 Z6.265\n\
N2250 X1.661 Y66.877 Z6.23\n\
N2260 X1.71 Y66.95 Z6.199\n\
N2270 X1.758 Y67.019 Z6.173\n\
N2280 X1.807 Y67.085 Z6.151\n\
N2290 X1.856 Y67.147 Z6.134\n\
N2300 X1.906 Y67.207 Z6.12\n\
N2310 X1.955 Y67.264 Z6.11\n\
N2320 X2.005 Y67.319 Z6.104\n\
N2330 X2.055 Y67.37 Z6.102\n\
N2340 X2.106 Y67.42 Z6.103\n\
N2350 X2.157 Y67.467 Z6.108\n\
N2360 X2.208 Y67.512 Z6.116\n\
N2370 X2.26 Y67.556 Z6.128\n\
N2380 X2.312 Y67.597 Z6.143\n\
N2390 X2.365 Y67.636 Z6.162\n\
N2400 X2.419 Y67.674 Z6.184\n\
N2410 X2.473 Y67.709 Z6.21\n\
N2420 X2.528 Y67.743 Z6.239\n\
N2430 X2.584 Y67.775 Z6.272\n\
N2440 X2.641 Y67.806 Z6.309\n\
N2450 X2.7 Y67.835 Z6.351\n\
N2460 X2.759 Y67.862 Z6.396\n\
N2470 X2.819 Y67.887 Z6.446\n\
N2480 X2.881 Y67.911 Z6.501\n\
N2490 X2.944 Y67.933 Z6.56\n\
N2500 X3.009 Y67.953 Z6.625\n\
N2510 X3.075 Y67.97 Z6.695\n\
N2520 X3.142 Y67.986 Z6.77\n\
N2530 X3.211 Y68. Z6.851\n\
N2540 X3.281 Y68.011 Z6.939\n\
N2550 X3.353 Y68.02 Z7.032\n\
N2560 X3.427 Y68.027 Z7.133\n\
N2570 X3.502 Y68.031 Z7.24\n\
N2580 X3.579 Y68.033 Z7.355\n\
N2590 X3.657 Y68.031 Z7.477\n\
N2600 X3.738 Y68.027 Z7.607\n\
N2610 X3.819 Y68.02 Z7.745\n\
N2620 X3.902 Y68.01 Z7.892\n\
N2630 X3.987 Y67.996 Z8.047\n\
N2640 X4.073 Y67.979 Z8.211\n\
N2650 X4.161 Y67.958 Z8.385\n\
N2660 X4.25 Y67.934 Z8.568\n\
N2670 X4.341 Y67.906 Z8.761\n\
N2680 X4.433 Y67.875 Z8.964\n\
N2690 X4.526 Y67.839 Z9.178\n\
N2700 X4.62 Y67.799 Z9.402\n\
N2710 X4.715 Y67.755 Z9.637\n\
N2720 X4.812 Y67.707 Z9.884\n\
N2730 X4.909 Y67.655 Z10.141\n\
N2740 X5.007 Y67.598 Z10.41";
*/
