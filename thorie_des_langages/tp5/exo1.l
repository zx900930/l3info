voyelle		[aeiouyAEIOUY]
consonne	[b-df-hj-np-tv-xzçB-DF-HJ-NP-TV-XZÇ]
lettre		[a-zA-Z]
%%
{voyelle}{lettre}+
{consonne}{lettre}+	printf("%s", yytext);
%%

