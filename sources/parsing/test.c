
// todo
// * echo $PWD; echo $PWD; cd .; pwd; echo $PWD; echo $PWD\n                                                   
// * echo $PWD; echo $PWD; cd ..; pwd; echo $PWD; echo $PWD\n                                                  
// * echo $PWD; echo $PWD; cd ../..; pwd; echo $PWD; echo $PWD\n                                               
// * echo $PWD; echo $PWD; cd ../../..; pwd; echo $PWD; echo $PWD\n                                            
// * echo $PWD; echo $PWD; cd ../../../..; pwd; echo $PWD; echo $PWD\n                                         
// * echo $PWD; echo $PWD; cd ../../../../..; pwd; echo $PWD; echo $PWD\n                                      
// * echo $PWD; echo $PWD; cd ../../../../../..; pwd; echo $PWD; echo $PWD\n                                   
// * echo $PWD; echo $PWD; cd /; pwd; echo $PWD; echo $PWD\n                                                   
// * echo $PWD; echo $PWD; cd ''; pwd; echo $PWD; echo $PWD\n                                                  
// * echo $PWD; echo $PWD; cd '' ''; pwd; echo $PWD; echo $PWD\n                                               
// * echo $PWD; echo $PWD; cd '' '' ''; pwd; echo $PWD; echo $PWD\n                                            
// * echo $PWD; echo $PWD; cd ' '; pwd; echo $PWD; echo $PWD\n                                                                       
// * export HOME='/home/tenshi' echo $PWD; echo $PWD; cd $HOME; pwd; echo $PWD; echo $PWD\n                 
// * echo $PWD; echo $PWD; cd /; pwd; echo $PWD; echo $PWD\n                                                   
// * echo $PWD; echo $PWD; cd /.; pwd; echo $PWD; echo $PWD\n                                                  
// * echo $PWD; echo $PWD; cd /./; pwd; echo $PWD; echo $PWD\n                                                 
// * echo $PWD; echo $PWD; cd /././././; pwd; echo $PWD; echo $PWD\n
// * cd ; cd Desktop/Minishell                                                                                          
// * echo $PWD; echo $PWD; cd ///; pwd; echo $PWD; echo $PWD\n                                                 
// * echo $PWD; echo $PWD; cd ////; pwd; echo $PWD; echo $PWD\n                                                
// * echo $PWD; echo $PWD; cd //////////////////////////////////////////////////////; pwd; echo $PWD; echo $OL... 
// * echo $PWD; echo $PWD; cd; echo $PWD\n                                                                     
// * export HOME='/home/tenshi' echo $PWD; echo $PWD; cd; echo $PWD; echo $PWD\n                            
// * echo $PWD; echo $PWD; cd ' /'; pwd; echo $PWD; echo $PWD\n                                                
// * echo $PWD; echo $PWD; cd ' / '; pwd; echo $PWD; echo $PWD\n                                               
// * echo $PWD; echo $PWD; cd '                  /'; pwd; echo $PWD; echo $PWD\n                               
// * echo $PWD; echo $PWD; cd '                  /              '; pwd; echo $PWD; echo $PWD\n                 
// * echo $PWD; echo $PWD; cd ' // '; pwd; echo $PWD; echo $PWD\n                                              
// * echo $PWD; echo $PWD; cd //home; pwd; echo $PWD; echo $PWD\n                                              
// * echo $PWD; echo $PWD; cd ' //home'; pwd; echo $PWD; echo $PWD\n                                           
// * echo $PWD; echo $PWD; cd '     //home    '; pwd; echo $PWD; echo $PWD\n                                                                           
// * echo $PWD; echo $PWD; cd /; echo $PWD; echo $PWD; unset PWD; cd /dev; echo $PWD\n                      
// * echo $PWD; echo $PWD; cd /; echo $PWD; echo $PWD; export PWD=bonjour; cd /dev; echo $PWD\n             
// *
// * echo\n                                                                                                          
// * echo bonjour\n                                                                                                  
// * echo lalalala lalalalal alalalalal alalalala\n                                                                  
// * echo lalalala                lalalalal      alalalalal alalalala\n                                              
// * echo Mollitia asperiores assumenda excepturi et ipsa. Nihil corporis facere aut a rem consequatur. Quas mole... 
// * echo -n\n                                                                                                       
// * echo -n bonjour\n                                                                                               
// * echo -n lalalala lalalalal alalalalal alalalala\n                                                               
// * echo -n lalalala                lalalalal      alalalalal alalalala\n                                           
// * echo -n Mollitia asperiores assumenda excepturi et ipsa. Nihil corporis facere aut a rem consequatur. Quas m... 
// * echo bonjour -n\n                                                                                               
// * echo -n bonjour -n\n                                                                                            
// *                         echo                     bonjour             je\n                                       
// *                         echo       -n            bonjour             je\n                                       
// * echo a '' b '' c '' d\n                                                                                         
// * echo a "" b "" c "" d\n                                                                                         
// * echo -n a '' b '' c '' d\n                                                                                      
// * echo -n a "" b "" c "" d\n                                                                                      
// * echo '' '' ''\n                                                                                                 
// * Echo bonjour\n                                                                                                  
// * eCho bonjour\n                                                                                                  
// * ecHo bonjour\n                                                                                                  
// * echO bonjour\n                                                                                                  
// * EchO bonjour\n                                                                                                  
// * eCHo bonjour\n                                                                                                  
// * EcHo bonjour\n                                                                                                  
// * eChO bonjour\n                                                                                                  
// * echo -n -n -n -n bonjour\n                                                                                      
// * echo -nnnnnnnnnnnnnnnnnnnnn bonjour\n                                                                           
// * echo -nnnnnnnnnnnnnnnnnnnnn -n -n -n bonjour -n -n\n                                                            
// * Cd .\n                                                                                                          
// * cD .\n                                                                                                          
// * export PATH='/bin:/usr/bin' Cd .\n                                                                           
// * export PATH='/bin:/usr/bin' cD .\n                                                                           
// * export PATH='/bin:/usr/bin' Echo bonjour\n                                                                   
// * export PATH='/bin:/usr/bin' eCho bonjour\n                                                                   
// * export PATH='/bin:/usr/bin' ecHo bonjour\n                                                                   
// * export PATH='/bin:/usr/bin' echO bonjour\n                                                                   
// * export PATH='/bin:/usr/bin' EchO bonjour\n                                                                   
// * export PATH='/bin:/usr/bin' eCHo bonjour\n                                                                   
// * export PATH='/bin:/usr/bin' EcHo bonjour\n                                                                   
// * export PATH='/bin:/usr/bin' eChO bonjour\n                                                                   
// * export PATH='/bin:/usr/bin' eChO 'bonjo\nur'\n                                                            

// * env\n                                                                                                                                                                            
// * Env\n                                                                                                           
// * enV\n                                                                                                           

// * exit\n                                                                                                          
// * exit 1\n                                                                                                        
// * exit 2\n                                                                                                        
// * exit 3\n                                                                                                        
// * exit ' 3'\n                                                                                                     
// * exit '\t3'\n                                                                                                    
// * exit '\t\f\r 3'\n                                                                                               
// * exit '3 '\n                                                                                                     
// * exit '3\t'\n                                                                                                    
// * exit '3\r'\n                                                                                                    
// * exit '3\t\f\r '\n                                                                                               
// * exit '3     a'\n                                                                                                
// * exit '3\t\t\ta'\n                                                                                               
// * exit 0\n                                                                                                        
// * exit -0\n                                                                                                       
// * exit -1\n                                                                                                       
// * exit 255\n                                                                                                      
// * exit 256\n                                                                                                      
// * exit 2000000\n                                                                                                  
// * exit -2000000\n                                                                                                 
// * exit 2147483647\n                                                                                               
// * exit -2147483648\n                                                                                              
// * exit 2147483648\n                                                                                               
// * exit -2147483649\n                                                                                              
// * exit 3147483648\n                                                                                               
// * exit -3147483649\n                                                                                              
// * exit 4294967295\n                                                                                               
// * exit 4294967296\n                                                                                               
// * exit -9223372036854775808\n                                                                                     
// * exit 9223372036854775807\n                                                                                      
// * exit -9223372036854775809\n                                                                                     
// * exit 9223372036854775808\n                                                                                      
// * exit 18446744073709551615\n                                                                                     
// * exit 18446744073709551616\n                                                                                     
// * exit +1\n                                                                                                       
// * exit +2\n                                                                                                       
// * exit +3\n                                                                                                       
// * exit +0\n                                                                                                       
// * exit +255\n                                                                                                     
// * exit +256\n                                                                                                     
// * exit +2000000\n                                                                                                 
// * exit +2147483647\n                                                                                              
// * exit ++1\n                                                                                                      
// * exit ++2\n                                                                                                      
// * exit ++3\n                                                                                                      
// * exit ++0\n                                                                                                      
// * exit ++255\n                                                                                                    
// * exit ++256\n                                                                                                    
// * exit ++2000000\n                                                                                                
// * exit ++2147483647\n                                                                                             
// * exit --1\n                                                                                                      
// * exit --2\n                                                                                                      
// * exit --3\n                                                                                                      
// * exit --0\n                                                                                                      
// * exit --255\n                                                                                                    
// * exit --256\n                                                                                                    
// * exit --2000000\n                                                                                                
// * exit --2147483647\n                                                                                             
// * exit bonjour\n                                                                                                  
// * exit 0_\n                                                                                                       
// * exit _0\n                                                                                                       
// * exit 0123456789\n                                                                                               
// * exit -0123456789\n                                                                                              
// * exit 00000000000000000000000000000000000000000000001\n                                                          
// * exit 0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\n           
// * exit 0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\n           
// * exit -0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001\n          
// * exit -9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999\n                
// * exit 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999\n                 
// * exit 0 bonjour\n                                                                                                
// * exit bonjour 0\n                                                                                                
// * exit 0 1\n                                                                                                      
// * exit 0 1 2 3 4 5 6 7 8 9\n                                                                                      
// * exit Mollitia asperiores assumenda excepturi et ipsa. Nihil corporis facere aut a rem consequatur. Quas mole... 
// * exit bonjoru; echo should have exited\n                                                                         
// * exit 99999999999999999999999999999999999999999999999999999; echo should have exited\n                           
// * exit 9999; echo should have exited\n                                                                            
// * Exit; echo a\n                                                                                                  
// * exiT; echo a\n      

// * export PATH='/bin:/usr/bin' Exit; echo a\n                                                                   
// * export PATH='/bin:/usr/bin' exiT; echo a\n                                                                   
// * export PATH='/bin:/usr/bin' Env\n                                                                            
// * export\n                                                                                                        
// * export A='' export\n                                                                                         
// * export A='"' export\n                                                                                        
// * export A='\' export\n                                                                                        
// * export A='$' export\n                                                                                        
// * export A='\t' export\n                                                                                       
// * export A=''' export\n                                                                                        
// * export A='a' export\n                                                                                        
// * export A=a; echo $A\n                                                                                           
// * export A=a B=b C=c; echo $A$B$C\n                                                                               
// * export A=a B=b C=c D=d E=e F=f G=g H=h I=i J=j K=k L=lM=m N=n O=o P=p Q=q R=r S=s T=t U=u V=v W=w X=x Y=y Z=... 
// * export BONJOURJESUIS=a; echo $BONJOURJESUIS\n                                                                   
// * export bonjourjesuis=a; echo $bonjourjesuis\n                                                                   
// * export bonjour_je_suis=a; echo $bonjour_je_suis\n                                                               
// * export BONJOURJESUIS1=a; echo $BONJOURJESUIS1\n                                                                 
// * export bO_nJq123o__1ju_je3234sui__a=a; echo $bO_nJq123o__1ju_je3234sui__a\n                                     
// * export a0123456789=a; echo $a0123456789\n                                                                       
// * export abcdefghijklmnopqrstuvwxyz=a; echo $abcdefghijklmnopqrstuvwxyz\n                                         
// * export ABCDEFGHIJKLMNOPQRSTUVWXYZ=a; echo $ABCDEFGHIJKLMNOPQRSTUVWXYZ\n                                         
// * export __________________________=a; echo $__________________________\n                                         
// * export _bonjour_=a; echo $_bonjour_\n                                                                           
// * export _=a; echo $_a\n                                                                                          
// * export 1=a\n                                                                                                    
// * export BONJOURJESUIS =a\n                                                                                       
// * export BONJOURJESUIS= a\n                                                                                       
// * export BONJOUR\\JESUIS=a\n                                                                                      
// * export BONJOUR\'JESUIS=a\n                                                                                      
// * export BONJOUR\"JESUIS=a\n                                                                                      
// * export BONJOUR\$JESUIS=a\n                                                                                      
// * export BONJOUR\&JESUIS=a\n                                                                                      
// * export BONJOUR\|JESUIS=a\n                                                                                      
// * export BONJOUR\;JESUIS=a\n                                                                                      
// * export BONJOUR\_JESUIS=a\n                                                                                      
// * export BONJOUR\0JESUIS=a\n                                                                                      
// * export \B\O\N\ \ \ \ \ \ \ JOURJESUIS=a\n                                                                       
// * export A=\B\O\N\ \ \ \ \ \ \ JOURJESUIS; echo $A\n                                                              
// * export A='bonjour je suis charles'; echo $A\n                                                                   
// * export A="bonjour je suis charles"; echo $A\n                                                                   
// * export A==a; echo $A\n                                                                                          
// * export A===a; echo $A\n                                                                                         
// * export A====a; echo $A\n                                                                                        
// * export A=====a; echo $A\n                                                                                       
// * export A======a; echo $A\n                                                                                      
// * export A=a=a=a=a=a; echo $A\n                                                                                   
// * export A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C; echo $A$B$C\n                                      
// * export 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C; echo $A$B$C\n                                        
// * export A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf '; echo $A$B$C\n                                        
// * export A B C; echo $A$B$C\n                                                                                     
// * export A B C; env\n                                                                                             
// * export 'AH@'=nop\n                                                                                              
// * export "AH'"=nop\n                                                                                              
// * export 'AH"'=nop\n                                                                                              
// * export 'AH$'=nop\n                                                                                              
// * export 'AH!'=nop\n                                                                                              
// * export 'AH|'=nop\n                                                                                              
// * export 'AH;'=nop\n                                                                                              
// * export 'AH&'=nop\n                                                                                              
// * export 'AH\'=nop\n                                                                                              
// * export TEST='A=a' export $TEST\n                                                                             
// * export BONJOUR\\JESUIS\n                                                                                        
// * export BONJOUR\'JESUIS\n                                                                                        
// * export BONJOUR\"JESUIS\n                                                                                        
// * export BONJOUR\$JESUIS\n                                                                                        
// * export BONJOUR\&JESUIS\n                                                                                        
// * export BONJOUR\|JESUIS\n                                                                                        
// * export BONJOUR\;JESUIS\n                                                                                        
// * export BONJOUR\_JESUIS\n                                                                                        
// * export BONJOUR\0JESUIS\n                                                                                        
// * Export B=bonjour\n                                                                                              
// * exporT B=bonjour\n                                                                                              
// * export PATH='/bin:/usr/bin' Export B=bonjour\n                                                               
// * export PATH='/bin:/usr/bin' exporT B=bonjour\n                                                               
// *                                                                                                            
// * export PATH='/bin:/usr/bin' Pwd\n                                                                            
// * export PATH='/bin:/usr/bin' pwD\n                                                                            
// * 
// * unset\n                                                                                                         
// * export A='a' unset A; echo $A\n                                                                              
// * export A='a' unset 'A '; echo $A\n                                                                           
// * export A='a' unset 'A='; echo $A\n                                                                           
// * export A='a' B='b' C='c' unset A B C; echo $A$B$C\n                                                          
// * export A='a' B='b' C='c' unset A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C; echo $A$B$C\n           
// * export A='a' B='b' C='c' unset 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C; echo $A$B$C\n             
// * export A='a' B='b' C='c' unset A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf '; echo $A$B$C\n             
// * export A='a' B='b' C='c' unset A; echo $A$B$C\n                                                              
// * export A='a' B='b' C='c' unset C; echo $A$B$C\n                                                              
// * export A='a' B='b' C='c' unset A B C\n                                                                       
// * export A='a' B='b' C='c' unset A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C\n                        
// * export A='a' B='b' C='c' unset 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf ' C\n                          
// * export A='a' B='b' C='c' unset A 'asdf ' B ' asdf asdf asd f' ' asdf ' '' 'asdf '\n                          
// * export A='a' B='b' C='c' unset A\n                                                                           
// * unset 'AH@'=nop\n                                                                                               
// * unset "AH'"=nop\n                                                                                               
// * unset 'AH"'=nop\n                                                                                               
// * unset 'AH$'=nop\n                                                                                               
// * unset 'AH!'=nop\n                                                                                               
// * unset 'AH|'=nop\n                                                                                               
// * unset 'AH;'=nop\n                                                                                               
// * unset 'AH&'=nop\n                                                                                               
// * unset 'AH\'=nop\n                                                                                               
// * Unset TERM\n                                                                                                    
// * unseT TERM\n                                                                                                    
// * export PATH='/bin:/usr/bin' Unset TERM\n                                                                     
// * export PATH='/bin:/usr/bin' unseT TERM\n                                                                     
// * 
// * notfound\n                                                                                                      
// * notfound a b c\n                                                                                                
// * echo "\"" >>a"b""c"  \n                                                                                         
// * echo\t\v\f\r�123456789:;=?@ABCDEFGHIJKLMNOPQRSTUVWXYZ\^_abcdefghijkl... 
// * echo foo>bar\n                                                                                                  
// * echo foo >bar\n                                                                                                 
// * echo foo> bar\n                                                                                                 
// * echo foo > bar\n                                                                                                
// * echo a as df sad f as df qw e  qwe  as df asd f as df as d fas d fasd f asd f asdf asdf  asdf  asd f asd f a... 
// * echo Mollitia asperiores assumenda excepturi et ipsa. Nihil corporis facere aut a rem consequatur. Quas mole... 
// * echo Mollitia asperiores assumenda excepturi et ipsa. Nihil corporis facere aut a rem consequatur. Quas mole... 
// * 
// * echo bonjour > test\n                                                                                           
// * echo > test bonjour\n                                                                                           
// * > test echo bonjour\n                                                                                           
// * echo bonjour >> test\n                                                                                          
// * echo >> test bonjour\n                                                                                          
// * >> test echo bonjour\n                                                                                                                                                               
// * echo bonjour > test\n                                                                                           
// * echo > test'sticked' bonjour\n                                                                                  
// * > test'sticked' echo bonjour\n                                                                                  
// * echo bonjour >> test'sticked'\n                                                                                 
// * echo >> test'sticked' bonjour\n                                                                                 
// * >> test'sticked' echo bonjour\n                                                                                 
// *                                                     
// *                                                   
// * echo > test"sticked" bonjour\n                                                                                  
// * > test"sticked" echo bonjour\n                                                                                  
// * echo bonjour >> test"sticked"\n                                                                                 
// * echo >> test"sticked" bonjour\n                                                                                 
// * >> test"sticked" echo bonjour\n                                                                                 
// *                                                       
// *                                                     
// * echo > test'yo'"sticked" bonjour\n                                                                              
// * > test'yo'"sticked" echo bonjour\n                                                                              
// * echo bonjour >> test'yo'"sticked"\n                                                                             
// * echo >> test'yo'"sticked" bonjour\n                                                                             
// * >> test'yo'"sticked" echo bonjour\n                                                                             
// *                                            
// *                                          
// * echo bonjour > test > je > suis\n                                                                               
// * echo > test > je bonjour > suis\n                                                                               
// * > test echo bonjour > je > suis\n                                                                               
// * echo bonjour >> test > je >> suis\n                                                                             
// * echo >> test bonjour > je > suis\n                                                                              
// * >> test echo > je bonjour > suis\n                                                                              
// *                                                  
// * echo bonjour>test>je>suis\n                                                                                     
// * >test echo bonjour>je>suis\n                                                                                    
// * echo bonjour>>test>je>>suis\n                                                                                   
// *                                                  
// * echo bonjour > a'b'c'd'e'f'g'h'i'j'k'l'm'n'o'p'q'r's't'u'v'w'x'y'z'\n                                           
// * echo bonjour > a"b"c"d"e"f"g"h"i"j"k"l"m"n"o"p"q"r"s"t"u"v"w"x"y"z"\n                                           
// * echo bonjour > a'b'c"d"e'f'g"h"i'j'k"l"m'n'o"p'q'r"s't'u"v"w"x"y'z'\n                                           
// * > file\n                                                                                                        
// *                                                                            
// * >\n                                                                                                             
// * >>\n                                                                                                            
// * <\n                                                                                                             
// * echo >\n                                                                                                        
// * echo >>\n                                                                                                       
// * echo <\n                                                                                                        
// * > test\n                                                                                                        
// * >> test\n                                                                                                       
// *                                                                                    
// * echo foo >>> bar\n                                                                                              
// * echo foo >>>> bar\n                                                                                             
// * echo foo >>>>> bar\n                                                                                            
// *                                                                      
// * cat < doesnotexist\n                                                                                                                                                                  
// * 
// * echo $?\n                                                                                                       
// * echo; echo $?\n                                                                                                 
// * notfound; echo $?\n                                                                                             
// * cat < doesntexist; echo $?\n                                                                                    
// * SETUP echo bonjour > noperm; chmod 000 noperm cat < noperm; echo $?\n                                         
// * echo\n                                                                                                          
// * notfound\n                                                                                                      
// * cat < doesntexist\n                                                                                             
// * SETUP echo bonjour > noperm; chmod 000 noperm cat < noperm\n                                                  
// * 
// * echo bonjour; echo je\n                                                                                         
// * echo bonjour ;echo je\n                                                                                         
// * echo bonjour ; echo je\n                                                                                        
// * echo bonjour;\n                                                                                                 
// * echo; \n                                                                                                        
// * echo ; \n                                                                                                       
// * echo ;\n                                                                                                        
// * ; echo\n                                                                                                        
// *  ;echo\n                                                                                                        
// *  ; echo\n                                                                                                       
// * echo a; echo b; echo c; echo d; echo e; echo f; echo g; echo h; echo i;echo j; echo k; echo l; echo m; echo ... 
// * echo a ; echo b; echo c ;echo d     ;   echo e   ;echo f;        echo g  ;echo h; echo i;echo j  ; echo k; e...                                                                               
// * echo bonjour; ls doesnotexists\n                                                                                
// * echo a ; ;\n                                                                                                    
// * echo a ; ;\n                                                                                                    
// * ;\n                                                                                                             
// * ; ;\n                                                                                                           
// * ; ; ;\n                                                                                                         
// * echo a ; ; echo b\n                                                                                             
// * ;;\n                                                                                                            
// * ;;;\n                                                                                                           
// * ;;;;;\n                                                                                                         
// * echo a ;; echo b\n                                                                                              
// * echo a ;;;;; echo b\n                                                                                           
// * < | a\n                                                                                                         
// * > | a\n                                                                                                         
// * >> | a\n                                                                                                        
// * < ; a\n                                                                                                         
// * > ; a\n                                                                                                         
// * >> ; a\n                                                                                                        
// * ; | a\n                                                                                                         
// * ; < a\n                                                                                                         
// * ; > a\n                                                                                                         
// * ; >> a\n                                                                                                        
// * | ; a\n                                                                                                         
// * | < a\n                                                                                                         
// * | > a\n                                                                                                         
// * | >> a\n                                                                                                        
// * > a ; a\n                                                                                                       
// * < a ; a\n                                                                                                       
// * >> a ; a\n                                                                                                      
// * Mollitia asperiores assumenda excepturi et ipsa. Nihil corporis facere aut a rem consequatur. Quas molestiae... 
// * Mollitia asperiores assumenda excepturi et ipsa. Nihil corporis facere aut a rem consequatur. Quas molestiae... 
// * Mollitia asperiores assumenda excepturi et ipsa. Nihil corporis facere aut a rem consequatur. Quas molestiae... 
// * Mollitia asperiores assumenda excepturi et ipsa. Nihil corporis facere aut a rem consequatur. Quas molestiae... 
// * 
// * echo $_\n                                                                                                       
// * echo; echo $_\n                                                                                                 
// * env; echo $_\n                                                                                                  
// * export A=a; echo $_\n                                                                                           
// * unset A; echo $_\n                                                                                              
// * echo a b c d; echo $_\n                                                                                         
// * cat -e /etc/shells; echo $_\n                                                                                   
// * echo a; echo "$_"\n                                                                                             
// * echo a; echo '$_'\n                                                                                             
// * echo a; echo "@$_@"\n                                                                                           
// * 
// * echo $SHLVL\n                                                                                                   
// * export SHLVL='' echo $SHLVL\n                                                                                
// * export SHLVL=' 1' echo $SHLVL\n                                                                              
// * export SHLVL=' 2' echo $SHLVL\n                                                                              
// * export SHLVL=' 3' echo $SHLVL\n                                                                              
// * export SHLVL=' ' 3'' echo $SHLVL\n                                                                           
// * export SHLVL=' '\t3'' echo $SHLVL\n                                                                          
// * export SHLVL=' '\t\f\r 3'' echo $SHLVL\n                                                                     
// * export SHLVL=' '3 '' echo $SHLVL\n                                                                           
// * export SHLVL=' '3\t'' echo $SHLVL\n                                                                          
// * export SHLVL=' '3\r'' echo $SHLVL\n                                                                          
// * export SHLVL=' '3\t\f\r '' echo $SHLVL\n                                                                     
// * export SHLVL=' '3     a'' echo $SHLVL\n                                                                      
// * export SHLVL=' '3\t\t\ta'' echo $SHLVL\n                                                                     
// * export SHLVL=' 0' echo $SHLVL\n                                                                              
// * export SHLVL=' -0' echo $SHLVL\n                                                                             
// * export SHLVL=' -1' echo $SHLVL\n                                                                             
// * export SHLVL=' 255' echo $SHLVL\n                                                                            
// * export SHLVL=' 256' echo $SHLVL\n                                                                            
// * export SHLVL=' 2000000' echo $SHLVL\n                                                                        
// * export SHLVL=' -2000000' echo $SHLVL\n                                                                       
// * export SHLVL=' 2147483647' echo $SHLVL\n                                                                     
// * export SHLVL=' -2147483648' echo $SHLVL\n                                                                    
// * export SHLVL=' 2147483648' echo $SHLVL\n                                                                     
// * export SHLVL=' -2147483649' echo $SHLVL\n                                                                    
// * export SHLVL=' 3147483648' echo $SHLVL\n                                                                     
// * export SHLVL=' -3147483649' echo $SHLVL\n                                                                    
// * export SHLVL=' 4294967295' echo $SHLVL\n                                                                     
// * export SHLVL=' 4294967296' echo $SHLVL\n                                                                     
// * export SHLVL=' -9223372036854775808' echo $SHLVL\n                                                           
// * export SHLVL=' 9223372036854775807' echo $SHLVL\n                                                            
// * export SHLVL=' -9223372036854775809' echo $SHLVL\n                                                           
// * export SHLVL=' 9223372036854775808' echo $SHLVL\n                                                            
// * export SHLVL=' 18446744073709551615' echo $SHLVL\n                                                           
// * export SHLVL=' 18446744073709551616' echo $SHLVL\n                                                           
// * export SHLVL=' +1' echo $SHLVL\n                                                                             
// * export SHLVL=' +2' echo $SHLVL\n                                                                             
// * export SHLVL=' +3' echo $SHLVL\n                                                                             
// * export SHLVL=' +0' echo $SHLVL\n                                                                             
// * export SHLVL=' +255' echo $SHLVL\n                                                                           
// * export SHLVL=' +256' echo $SHLVL\n                                                                           
// * export SHLVL=' +2000000' echo $SHLVL\n                                                                       
// * export SHLVL=' +2147483647' echo $SHLVL\n                                                                    
// * export SHLVL=' ++1' echo $SHLVL\n                                                                            
// * export SHLVL=' ++2' echo $SHLVL\n                                                                            
// * export SHLVL=' ++3' echo $SHLVL\n                                                                            
// * export SHLVL=' ++0' echo $SHLVL\n                                                                            
// * export SHLVL=' ++255' echo $SHLVL\n                                                                          
// * export SHLVL=' ++256' echo $SHLVL\n                                                                          
// * export SHLVL=' ++2000000' echo $SHLVL\n                                                                      
// * export SHLVL=' ++2147483647' echo $SHLVL\n                                                                   
// * export SHLVL=' --1' echo $SHLVL\n                                                                            
// * export SHLVL=' --2' echo $SHLVL\n                                                                            
// * export SHLVL=' --3' echo $SHLVL\n                                                                            
// * export SHLVL=' --0' echo $SHLVL\n                                                                            
// * export SHLVL=' --255' echo $SHLVL\n                                                                          
// * export SHLVL=' --256' echo $SHLVL\n                                                                          
// * export SHLVL=' --2000000' echo $SHLVL\n                                                                      
// * export SHLVL=' --2147483647' echo $SHLVL\n                                                                   
// * export SHLVL=' bonjour' echo $SHLVL\n                                                                        
// * export SHLVL=' 0_' echo $SHLVL\n                                                                             
// * export SHLVL=' _0' echo $SHLVL\n                                                                             
// * export SHLVL=' 0123456789' echo $SHLVL\n                                                                     
// * export SHLVL=' -0123456789' echo $SHLVL\n                                                                    
// * export SHLVL=' 00000000000000000000000000000000000000000000001' echo $SHLVL\n                                
// * export SHLVL=' 0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000... 
// * 
// * export PATH='doesnotexits' echo $PATH\n                                                                      
// * export PATH='doesnotexits:asdfasdfas' echo $PATH\n                                                           
// * export PATH='a:b:c:d:e:f:g:h:i:j:k:l:m:n:o:p:q:r:s:t:u:v:w:x:y:z' echo $PATH\n                               
// * export PATH='________' echo $PATH\n                                                                          
// * export PATH='        ' echo $PATH\n                                                                          
// * export PATH='   :    ' echo $PATH\n                                                                          
// * export PATH='     /bin      ' echo $PATH\n                                                                   
// * export PATH='     /sbin      ' echo $PATH\n                                                                  
// * export PATH='/bin:/bin:/bin:/bin' echo $PATH\n                                                               
// * export PATH='/sbin:/sbin:/sbin:/sbin' echo $PATH\n                                                           
// * export PATH='' echo $PATH\n                                                                                  
// * export PATH=':' echo $PATH\n                                                                                 
// * export PATH=':::::::::::::::::::' echo $PATH\n                                                               
// * export PATH='/asdfasdf' echo $PATH\n                                                                         
// * export PATH='/usr/asdf:/usr/lib/asdfasdf' echo $PATH\n                                                       
// * export PATH='doesnotexits' whoami\n                                                                          
// * export PATH='doesnotexits:asdfasdfas' whoami\n                                                               
// * export PATH='a:b:c:d:e:f:g:h:i:j:k:l:m:n:o:p:q:r:s:t:u:v:w:x:y:z' whoami\n                                   
// * export PATH='________' whoami\n                                                                              
// * export PATH='        ' whoami\n                                                                              
// * export PATH='   :    ' whoami\n                                                                              
// * export PATH='     /usr/bin      ' whoami\n                                                                   
// * export PATH='/usr/bin:/usr/bin:/usr/bin:/usr/bin' whoami\n                                                   
// * export PATH='     /sbin      ' whoami\n                                                                      
// * export PATH='/sbin:/sbin:/sbin:/sbin' whoami\n                                                               
// * export PATH='' whoami\n                                                                                      
// * unset PATH; whoami\n                                                                                            
// * export PATH=':' whoami\n                                                                                     
// * export PATH=':::::::::::::::::::' whoami\n                                                                   
// * export PATH='/asdfasdf' whoami\n                                                                             
// * export PATH='/usr/asdf:/usr/lib/asdfasdf' whoami\n                                                           
// * export PATH='/usr/bin' Whoami\n                                                                              
// * export PATH='/usr/bin' wHoAMi\n                                                                              
// * export PATH='/usr/bIn' whoami\n                                                                              
// * export PATH='/Usr/bin' whoami\n                                                                              
// * export PATH='/usr/bIn' Whoami\n                                                                              
// * export PATH='/Usr/bin' wHoami\n                                                                              
// * export PATH='' Whoami\n                                                                                      
// * export PATH='' wHoami\n                                                                                      
// * 
// * echo \a\n                                                                                                       
// * \e\c\h\o bonjour\n                                                                                              
// * echo charles\ \n                                                                                                
// * echo \ \ jesuis\ \ charles\n                                                                                    
// * echo \ \ jesuis\; \ charles\n                                                                                   
// * echo \ \ jesuis\&\& \ charles\n                                                                                 
// * echo \ \ jesuis\|\| \ charles\n                                                                                 
// * echo \ \ jesuis \|\| \ charles\n                                                                                
// * echo \ \ jesuis\; \ charles\n                                                                                   
// * echo \ \ \ \ \ \ \ \ \n                                                                                         
// * echo \ \ \ \ \ \ \ \               \ \ \ \ \ \ \n                                                               
// * echo \$PATH\n                                                                                                   
// * echo \$\P\A\T\H\n                                                                                               
// * echo\ bonjour\n                                                                                                 
// * \ echo bonjour\n                                                                                                
// *  \ echo bonjour\n                                                                                               
// *                  \ echo bonjour\n                                                                               
// *  \                 echo bonjour\n                                                                               
// *                  \                    echo bonjour\n                                                                                                                                                      
// * echo \\n                                                                                                        
// * echo "\""'bonjour'\n                                                                                            
// * 
// * export TEST='bonjour' echo $TEST\n                                                                           
// * export TEST='bonjour' echo $TES\n                                                                            
// * export TEST='bonjour' echo $TEST_\n                                                                          
// * export TEST='bonjour' echo "|$TEST|"\n                                                                       
// * export TEST='bonjour' echo "|$TES|"\n                                                                        
// * export TEST='bonjour' echo "|$TEST_|"\n                                                                      
// * export TEST='bonjour' echo '|$TEST|'\n                                                                       
// * export TEST='bonjour' echo '|$TES|'\n                                                                        
// * export TEST='bonjour' echo '|$TEST_|'\n                                                                      
// * export A='foo' B='bar' C='baz' echo $A$B$C\n                                                                 
// * export A='foo' B='bar' C='baz' echo "$A$B$C"\n                                                               
// * export A='foo' B='bar' C='baz' echo '$A$B$C'\n                                                               
// * export A='foo' B='bar' C='baz' echo $A,$B,$C\n                                                               
// * export A='foo' B='bar' C='baz' echo "$A,$B,$C"\n                                                             
// * export A='foo' B='bar' C='baz' echo '$A,$B,$C'\n                                                             
// * export A='foo' B='bar' C='baz' echo $A"$B"$C"A"$B"$C"\n                                                      
// * export A='foo' B='bar' C='baz' echo $A'$B'$C'A'$B'$C'\n                                                      
// * export A='foo ' B=' bar  ' C='baz ' echo $A"$B"$C"A"$B"$C"\n                                                 
// * export A='foo ' B=' bar  ' C='baz ' echo $A'$B'$C'A'$B'$C'\n                                                 
// * echo $A\n                                                                                                       
// * echo $A$B\n                                                                                                     
// * echo $A$B$C\n                                                                                                   
// * echo $A$B$C$D\n                                                                                                 
// * export A='bonjour\je' echo $A\n                                                                            
// * export A='\b\\o\\\nj\\\\\\\our\\je\\\\' echo $A\n                                                          
// * export A='   \b\\o\\\nj\\\\\\\our\\je\\\\' echo $A\n                                                       
// * export A='\b\\o\\\nj\\\\\\\our\\je\\\\   ' echo $A\n                                                       
// * export A='  \b\\o\\\nj\\\\\\\our\\je\\\\ ' echo $A\n                                                       
// * export A='a  \b\\o\\\nj\\\\\\\our\\je\\\\ b' echo $A\n                                                     
// * export A=' a  \b\\o\\\nj\\\\\\\our\\je\\\\ b ' echo $A\n                                                   
// * export A=' ' echo $A\n                                                                                     
// * export A='    ' echo $A\n                                                                                  
// * export A='\ ' echo $A\n                                                                                    
// * export A=' \  ' echo $A\n                                                                                  
// * export A='bonjour' echo \ \ \ \ \ \ \ $A\ \ \ \ \ \ \n                                                       
// * export A='bonjour je suis' echo \ \ \ \ \ \ \ $A\ \ \ \ \ \ \n                                               
// * export A='  bonjour je suis  ' echo \ \ \ \ \ \ \ $A\ \ \ \ \ \ \n                                           
// * export A='bonjour je suis splited' echo $A\n                                                                 
// * export A='bonjour     je     suis    splited' echo $A\n                                                      
// * export A='   bonjour     je     suis    splited   ' echo $A\n                                                
// * export A='bonjour je suis splited' echo $A\n                                                               
// * export A='bonjour     je     suis    splited' echo $A\n                                                    
// * export A='   bonjour     je     suis    splited   ' echo $A\n                                              
// * export A='bonjour je suis splited' echo "$A"\n                                                             
// * export A='bonjour     je     suis    splited' echo "$A"\n                                                  
// * export A='   bonjour     je     suis    splited   ' echo "$A"\n                                            
// * export A='bonjour je suis splited' echo \ $A\n                                                               
// * export A='bonjour     je     suis    splited' echo \ $A\n                                                    
// * export A='   bonjour     je     suis    splited   ' echo \ $A\n                                              
// * export A='bonjour je suis splited' echo $A\ \n                                                               
// * export A='bonjour     je     suis    splited' echo $A\ \n                                                    
// * export A='   bonjour     je     suis    splited   ' echo $A\ \n                                              
// * export A='   bonjour     je     suis    splited   ' echo $A$A$A\n                                            
// * export A=''Mollitia asperiores assumenda excepturi et ipsa. Nihil corporis facere aut a rem consequatur. Q... 
// * export A=''Mollitia asperiores assumenda excepturi et ipsa. Nihil corporis facere aut a rem consequatur. Q... 
// * export A=''Mollitia asperiores assumenda excepturi et ipsa. Nihil corporis facere aut a rem consequatur. Q... 
// * export ECHO='echo' $ECHO $ECHO\n                                                                             
// * export A='ec' B='ho' $A$B bonjour\n                                                                          
// * SETUP touch a b c export LS='ls -l' $LS\n                                                                  
// * echo $\n                                                                                                        
// * echo \$\n                                                                                                       
// * echo \$\$\$\$\n                                                                                                 
// * echo \$$\$$\n                                                                                                   
// * export A='a' B='b' echo $\A $\B\n                                                                            
// * export A='a' B='b' echo $\A$\B\n                                                                             
// * export A=' ' echo $A\n                                                                                       
// * export A='  ' echo $A\n                                                                                      
// * export A='   ' echo $A\n                                                                                     
// * export A='    ' echo $A\n                                                                                    
// * export A='  a ' echo $A\n                                                                                    
// * export A='                                ' echo $A\n                                                        
// * export A='                     a          ' echo $A\n                                                        
// * export A=' ' echo @$A@\n                                                                                     
// * export A=' ' echo @ $A@\n                                                                                    
// * export A=' ' echo @$A @\n                                                                                    
// * export A='       ' echo @$A@\n                                                                               
// * export A=' ' echo '@'$A'@'\n                                                                                 
// * export A=' ' echo '@' $A'@'\n                                                                                
// * export A=' ' echo '@'$A '@'\n                                                                                
// * export A=' ' echo "@"$A"@"\n                                                                                 
// * export A=' ' echo "@" $A"@"\n                                                                                
// * export A=' ' echo "@"$A "@"\n                                                                                
// * export A=' ' echo @"$A"@\n                                                                                   
// * export A=' ' echo @ "$A"@\n                                                                                  
// * export A=' ' echo @"$A" @\n                                                                                  
// * export A='       ' echo @"$A"@\n                                                                             
// * export A=' ' echo '@'"$A"'@'\n                                                                               
// * export A=' ' echo '@' "$A"'@'\n                                                                              
// * export A=' ' echo '@'"$A" '@'\n                                                                              
// * export A=' ' echo "@""$A""@"\n                                                                               
// * export A=' ' echo "@" "$A""@"\n                                                                              
// * export A=' ' echo "@""$A" "@"\n                                                                              
// * export A='' B='' C='' echo $A$B$C\n                                                                          
// * export A='file' echo bonjour > $A\n                                                                          
// * export A='fi le' echo bonjour > $A\n                                                                         
// * export A='fi le' echo bonjour > "$A"\n                                                                       
// * export A='fi le' echo bonjour > '$A'\n                                                                       
// * 
// * 'echo' 'bonjour'\n                                                                                              
// * 'echo' 'je' 'suis' 'charles'\n                                                                                  
// * "echo" "bonjour"\n                                                                                              
// * "echo" "je" "suis" "charles"\n                                                                                  
// * echo je'suis'"charles"\n                                                                                        
// * echo "je"suis'charles'\n                                                                                        
// * echo 'je'"suis"charles\n                                                                                        
// * echo "\""\n                                                                                                     
// * echo "\$"\n                                                                                                     
// * echo "\\"\n                                                                                                     
// * echo "\a"\n                                                                                                     
// * echo "\A"\n                                                                                                     
// * ls ""\n                                                                                                         
// * ls ''\n                                                                                                         
// * ls "" "" "" '' """"\n                                                                                           
// * ls '' '' '''' ''\n                                                                                              
// * '     echo' bonjour\n                                                                                           
// * 'echo     ' bonjour\n                                                                                           
// * "     echo" bonjour\n                                                                                           
// * "echo     " bonjour\n                                                                                           
// * ''echo bonjour\n                                                                                                
// * ""echo bonjour\n                                                                                                
// * ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''echo bonjour\n                                        
// * """"""""""""""""""""""""""""""""""""""""""""""""""""""""""echo bonjour\n                                        
// * echo'' bonjour\n                                                                                                
// * echo"" bonjour\n                                                                                                
// * echo'''''''''''''''''''''''''''''''''''''''''''''''''''''''''' bonjour\n                                        
// * echo"""""""""""""""""""""""""""""""""""""""""""""""""""""""""" bonjour\n                                        
// * ec''ho bonjour\n                                                                                                
// * ec""ho bonjour\n                                                                                                
// * ec''''''''''''''''''''''''''''''''''''''''''''''''''''''''''ho bonjour\n                                        
// * ec""""""""""""""""""""""""""""""""""""""""""""""""""""""""""ho bonjour\n                                        
// * '''''''e''''''''''c''''''''''''h''''''''o''''''''''''''''''''' bonjour\n                                        
// * """""""e""""""""""c""""""""""""h""""""""o""""""""""""""""""""" bonjour\n                                        
// * echo '"'\n                                                                                                      
// * echo '""""""""""""""""""""""""""'\n                                                                             
// * echo "'"\n                                                                                                      
// * echo "''''''''''''''''''''''''''"\n                                                                             
// * echo '\n                                                                                                        
// * echo "\n                                                                                                        
// * echo '''\n                                                                                                      
// * echo """\n                                                                                                      
// * echo '''''''''''''''''''''''''''''''''''''''''''\n                                                              
// * echo """""""""""""""""""""""""""""""""""""""""""\n                                                              
// * echo 'AH\'\n                                                                                                    
// * echo "AH\"\n                                                                                                    
// * echo "AH\""\n                                                                                                   
// * echo '\''\n                                                                                                     
// * echo "\""\n                                                                                                     
// * echo "\\""\n                                                                                                    
// * echo bonjour > "fi le"\n                                                                                        
// * echo bonjour > 'fi le'\n                                                                                        
// * echo foo\n                                                                                                      
// * echo                    foo\n                                                                                   
// *              echo foo\n                                                                                         
// * echo foo             \n                                                                                         
// *          echo           foo             \n                                                                      
// * echo\t\t\t\t\t\t\t\t\t\tfoo\n                                                                                   
// * \t\t\t\t\t\techo\tfoo\n                                                                                         
// * echo\tfoo\t\t\t\t\t\t\n                                                                                         
// * \t\t\t\techo\t\t\t\tfoo\t\t\t\t\n                                                                               
// * \fecho\ffoo\n                                                                                                   
// * \necho\nfoo\n                                                                                                   
// * \recho\rfoo\n                                                                                                   
// * \vecho\vfoo\n                                                                                                   
// * \t\r\v\fecho\v\t\r\vfoo\n                                                                                       
// * \n                                                                                                              
// *                                           \n                                                                    
// * \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n                                                                    
// *             \t\t\t           \t\t\t       \n                                                                    