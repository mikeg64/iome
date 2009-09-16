function [veccell]=vec2cellarray( vec )

    vlen=length(vec);
    veccell=cell(vlen,1);
    %vec=zeros(vlen,1);
    for i = 1:vlen
       veccell{i} = num2str(vec(i));
    end

