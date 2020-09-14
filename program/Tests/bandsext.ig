img pencils="../test/Images/pencils.jpg";

out="../test/Images/band";

i=0;
while(i<=2) do{
		extractBand(pencils, out+i+".jpg", i);
		i=i+1;
}
