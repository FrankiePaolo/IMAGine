%Rif=im2double(imread("2Appello/e4/Rif.bmp"));
tic
    im=im2double(imread("GaussianNoise.bmp"));
    %dimensione del filtro
    filter_size=5;
    %media
    filtro_media=fspecial('average', filter_size);
    im_avg=imfilter(im, filtro_media, 'conv', 'circular');
time = toc;