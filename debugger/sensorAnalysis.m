voltage = 0:0.1:4.5;
turbidity = -1120.4.*voltage.^2+5742.3.*voltage-4352.9;

plot(voltage, turbidity);
grid