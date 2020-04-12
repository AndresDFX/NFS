#!/usr/bin/octave
close all
arg_list = argv();
w = str2num(arg_list{1});
hw = floor(w/2);
u = linspace(-hw, hw, w);
v = linspace(-hw, hw, w);
[uu, vv] = meshgrid(u,v);
sigma = 4;
g = exp(-(uu.^2 + vv.^2)/(2*sigma^2));
g /= sum(g(:));
colormap(jet(10));
clf();
surf(uu,vv,g);
print(arg_list{2},"-dpng");
