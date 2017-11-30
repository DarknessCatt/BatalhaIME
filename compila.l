D [0-9]
L [a-zA-Z_]
H [a-zA-Z_0-9]
E [Ee][+-]?{D}+

%{
#include <math.h>
#include "compila.tab.h"
%}


%%
{D}*[.]?{D}+{E}?	{ yylval.val = atof(yytext); return NUMt; }

ret(urn)?  { return RETt; }

if      { return IF; }
while	{ return WHILE; }
func|def { return FUNC; }
print   { return PRINT; }


{L}{H}* { 
  strncpy(yylval.cod, yytext, 30);
  return ID;
}

[ \t\n]+	/* pula espacos em branco */

#.*		/* comentarios simples */

;		{ return EOL; }
,		{ return SEP; }
=		{ return ASGN; }
[(]		{ return OPEN; }
[)]		{ return CLOSE; }
[{]		{ return ABRE; }
[}]		{ return FECHA; }
[+]		{ return ADDt; }
[-]		{ return SUBt; }
[*]		{ return MULt; }
[/]		{ return DIVt; }
==		{ return EQt; }
!=		{ return NEt; }
"<"		{ return LTt; }
"<="	{ return LEt; }
">"		{ return GTt; }
">="	{ return GEt; }

.	{  fprintf(stderr, "Entrada ignorada\n-->%s\n", yytext); }

%%

/* Local Variables: */
/* mode: c */
/* End: */
