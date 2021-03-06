clear;
close;
clc;

image = load('sampleM.txt');
x27=image(:,2);
y27=image(:,3);
xr=image(:,4);
yr=image(:,5);
xo = [0;0;0;0;0];
criteria = -1;
counter=0;
while(criteria == -1)
A = [];
w = [];
for i=1:6
[determin,W] = deter(x27(i,1),y27(i,1),xr(i,1),yr(i,1),xo);
A = [A;determin];
w = [w;W];
end
N= transpose(A)*A;
Ninv = inv(N);
delta = -Ninv*transpose(A)*w;
xhat = xo-delta;
if(abs(max(delta))<1)
    criteria = 1;
end
  xo=xhat;
  counter = counter+1;
end

function [deter,w] = deter(x27,y27,xr,yr,xo)
zr=0;
bx=92;
by=xo(1,1);
bz=xo(2,1);
c= 153.358;
omega =xo(3,1);
kappa = xo(5,1);
phi = xo(4,1);
Right = [xr; yr; 0];
M = rotz(rad2deg(kappa))*roty(rad2deg(phi))*rotx(rad2deg(omega));
Rt = transpose(M)*Right;
xr = Rt(1,1);
yr = Rt(2,1);
zr = Rt(3,1);

	Mby =[ 0, 1, 0;
		x27, y27, -c;
		xr, yr, zr];
	
	Mbz =[0, 0, 1;
		x27, y27, -c;
		xr, yr, zr];

	Momega =[ bx, by, bz;
		x27, y27, -c;
		0, -zr, yr];

	Mphi=[ bx, by, bz;
		x27, y27, -c;
		-yr*sin(omega)+zr*cos(omega), xr*sin(omega), -xr*cos(omega)];
	Mkappa =[ bx, by, bz;
		x27, y27, -c;
		-yr*cos(omega)*cos(phi)-zr*sin(omega)*cos(phi), xr*cos(omega)*cos(phi)-zr*sin(phi), xr*sin(omega)*cos(phi)+yr*sin(phi)];

	Mw =[ bx, by, bz;
		x27, y27, -c;
		xr, yr, zr];
    deter = [ det(Mby),det(Mbz), det(Momega),det(Mphi),det(Mkappa)];
    w = det(Mw);
end