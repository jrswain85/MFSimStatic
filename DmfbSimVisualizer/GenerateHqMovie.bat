..\Shared\mencoder.exe -mc 0 -noskip -skiplimit 0 -ovc lavc -lavcopts vcodec=mpeg4:vhq:trell:mbd=2:vmax_b_frames=1:v4mv:vb_strategy=0:vlelim=0:vcelim=0:cmp=6:subcmp=6:precmp=6:predia=3:dia=3:vme=4:vqscale=1 "mf://@order.txt" -mf type=png:fps=100 -o Sim\Movie_HQ.avi