function [vec]=cellarray2vec( veccell )

    vlen=length(veccell);
    vec=zeros(1,vlen);
    for i = 1:vlen
       vec(1,i) = str2num(veccell{i});
    end