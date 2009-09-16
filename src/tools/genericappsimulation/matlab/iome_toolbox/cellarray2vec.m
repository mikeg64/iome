function [vec]=cellarray2vec( veccell )

    vlen=length(veccell);
    vec=zeros(vlen,1);
    for i = 1:vlen
       vec(i) = str2num(veccell{i});
    end