X=Xpar
Xsel=Xpar;
[Npop,n]=size(X);n=n-1;
[Fsort,ind]=sort(X(:,n+1));
X=X(ind,:);
p=1:Npop;roulette=cumsum(p)/sum(p);
for i=1:Npop;
  u=rand();
  index=find(roulette<u);Nselect=max(index);
  Xsel(i,:)=X(Nselect,:);
end