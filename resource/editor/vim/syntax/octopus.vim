syntax keyword wKeyword if endif while for in continue print input or and func ret endfor
syntax keyword wKeywordTypes int string double boolean 
syntax match wComment "\v#.*$"
syntax match wOperator "\v\*"
syntax match wOperator "\v/"
syntax match wOperator "\v\+"
syntax match wOperator "\v-"
syntax match wOperator "\v\?"
syntax match wOperator "\v\*\="
syntax match wOperator "\v/\="
syntax match wOperator "\v\+\="
syntax match wOperator "\v-\="
syntax region wString start=/\v"/ skip=/\v\\./ end=/\v"/

highlight link wString String
highlight link wComment Comment
highlight link wKeyword Keyword
highlight link wKeywordTypes KeywordType
highlight link wOperator Operator

highlight KeywordType ctermfg=blue
highlight wKeyword ctermfg=green
