      PARAMETER (KSZJ=4000,MAX_TRACKS=100,ntbase=3000)
C...Preamble: declarations.
 
C...All real arithmetic in double precision.
      IMPLICIT DOUBLE PRECISION(A-H, O-Z)
      PARAMETER (Pi=3.14159275)
C...Three Pythia functions return integers, so need declaring.
      INTEGER PYK,PYCHGE,PYCOMP

C...EXTERNAL statement links PYDATA on most machines.
      EXTERNAL PYDATA

      COMMON/PYDAT1/MSTU(200),PARU(200),MSTJ(200),PARJ(200)
      COMMON/PYDAT3/MDCY(500,3),MDME(8000,2),BRAT(8000),KFDP(8000,5)
      COMMON/PYDAT2/KCHG(500,4),PMAS(500,4),PARF(2000),VCKM(4,4) 
      COMMON/PYPARS/MSTP(200),PARP(200),MSTI(200),PARI(200) 
      COMMON/PYJETS/N,NPAD,K(KSZJ,5),P(KSZJ,5),V(KSZJ,5)
      COMMON/PYSUBS/MSEL,MSELPD,MSUB(500),KFIN(2,-40:40),CKIN(200)
      COMMON/QUEST/IQUEST(100)

      integer*4 mult,tracks

      integer*4 tracksd,tracksb,tracksmb

      real*4 elecptd4nt,hadronptd4nt,dphid4nt
      real*4 elecptb4nt,hadronptb4nt,dphib4nt
      real*4 elecptmb4nt,hadronptmb4nt,dphimb4nt
      real*4 d_hadronptd4nt,d_dphid4nt
      real*4 b_hadronptb4nt,b_dphib4nt	
  

      integer*4 ntram2535,ntrad2535,ntrab2535,ntram3545,
     & ntrad3545,ntrab3545,ntram4555,ntrad4555,ntrab4555

      integer*4 ntradfra2535,ntrabfra2535,ntradfra3545,
     &ntrabfra3545,ntradfra4555,ntrabfra4555

      integer*4 hneg,nevent
      character*512 name_string

      real*4 elecetam,elecphim,detam,dphim,elecptm,dphi2m
      real*4 elecetad,elecphid,detad,dphid,elecptd,dphi2d
      real*4 elecetab,elecphib,detab,dphib,elecptb,dphi2b
      real*4 parentptb,parentptd,parentptm

c*******************for openning angle*******************
      real*4 elecpxd,elecpyd,elecpzd,elecpd
      real*4 hadronpxd,hadronpyd,hadronpzd,hadronpd
      real*4 elecpxb,elecpyb,elecpzb,elecpb
      real*4 hadronpxb,hadronpyb,hadronpzb,hadronpb	
      real*4 thetad,thetab
      real*4 cosvalued,cosvalueb
c*****************************************************
	
      real*4 allhadptd,allhadptb
      real*4 dhadptd,bhadptb

      real*4 detadfra,detabfra,dphidfra,dphibfra
      real*4 dphi2dfra,dphi2bfra,dphimfra,dphi2mfra
      real*4 detamfra,deta2mfra

      real*4 tram2535,trad2535,trab2535,tram3545,
     &trad3545,trab3545,tram4555,trad4555,trab4555

      real*4 tradfra2535,trabfra2535,tradfra3545,
     &trabfra3545,tradfra4555,trabfra4555

      real*4 sumptm2535,sumptd2535,sumptb2535,sumptm3545,
     &sumptd3545,sumptb3545,sumptm4555,sumptd4555,sumptb4555

      real*4 sumptdfra2535,sumptbfra2535,sumptdfra3545,
     &sumptbfra3545,sumptdfra4555,sumptbfra4555

c      real*4 pt1,pt2,y1,y2,eta1,phi1
c      integer*4 decaynot1,decaynot2,decaynot3
c      integer*4 kflag
      
c      integer*4 ny3,ny4
c      dimension ny1(30),ny2(30),ny3(30),ny4(30)
C       common /event_general/mult,hneg,nevent
c       common /event_track/tracks,pt(MAX_TRACKS),rap(MAX_TRACKS),
c     &      eta(MAX_TRACKS),phi(MAX_TRACKS),
c     &      decaynot1(MAX_TRACKS),decaynot2(MAX_TRACKS),
c     &      decaynot3(MAX_TRACKS),
c     &      kflag(MAX_TRACKS),eparentpt(MAX_TRACKS)

	common /event_trackd/tracksd,elecptd4nt(MAX_TRACKS),
     &  hadronptd4nt(MAX_TRACKS),dphid4nt(MAX_TRACKS),
     &  d_hadronptd4nt(MAX_TRACKS),d_dphid4nt(MAX_TRACKS)

        common /event_trackb/tracksb,elecptb4nt(MAX_TRACKS),
     &  hadronptb4nt(MAX_TRACKS),dphib4nt(MAX_TRACKS),
     &  b_hadronptb4nt(MAX_TRACKS),b_dphib4nt(MAX_TRACKS)

        common /event_trackmb/tracksmb,elecptmb4nt(MAX_TRACKS),
     &  hadronptmb4nt(MAX_TRACKS),dphimb4nt(MAX_TRACKS)

      SAVE /PYDAT1/,/PYJETS/,/PYDAT3/
      integer*4      hmemor(1000000)
      character*6    varname(8)
      real*4 values(8),tmpvaluesd(100,5)
      real*4 tmpvaluesb(100,5),tmpvaluesmb(100,3)
      COMMON /PAWC/ HMEMOR
        INTEGER MM(50),KPA(50)
      COMMON/PYDATR/MRPY(6),RRPY(100) 
  
      CALL HLIMIT(1000000)
      IQUEST(10)=256000
c      CALL HROPEN(55,'EXAM','minbias0.hist',
c     &     'NQ',8192,ISTAT)
      CALL HROPEN(55,'EXAM','minbias0.hist',
     &     'NQ',8190,ISTAT)
c*******jet cone 0.35 by 0.35****************************
      call hbook1(125350,'ntracks distribution e from B, 
     &2.5<pt(e)<3.5',10,0.5,10.5,0.)
      call hbook1(125351,'sumpt distribution e from B, 
     &2.5<pt(e)<3.5',30,0.,15.,0.)

      call hbook1(25350,'ntracks distribution e from D,
     &2.5<pt(e)<3.5',10,0.5,10.5,0.)
      call hbook1(25351,'sumpt distribution e from D,
     &2.5<pt(e)<3.5',30,0.,15.,0.)

      call hbook1(225350,'ntracks distribution Minbias,
     &2.5<pt(e)<3.5',10,0.5,10.5,0.)
      call hbook1(225351,'sumpt distribution Minbias,
     &2.5<pt(e)<3.5',30,0.,15.,0.)

      call hbook1(135450,'ntracks distribution e from B, 
     &3.5<pt(e)<4.5',10,0.5,10.5,0.)
      call hbook1(135451,'sumpt distribution e from B, 
     &3.5<pt(e)<4.5',30,0.,15.,0.)

      call hbook1(35450,'ntracks distribution e from D,
     &3.5<pt(e)<4.5',10,0.5,10.5,0.)
      call hbook1(35451,'sumpt distribution e from D,
     &3.5<pt(e)<4.5',30,0.,15.,0.)

      call hbook1(235450,'ntracks distribution Minbias,
     &3.5<pt(e)<4.5',10,0.5,10.5,0.)
      call hbook1(235451,'sumpt distribution Minbias,
     &3.5<pt(e)<4.5',30,0.,15.,0.)

      call hbook1(145550,'ntracks distribution e from B,
     &4.5<pt(e)<5.5',10,0.5,10.5,0.)
      call hbook1(145551,'sumpt distribution e from B,
     &4.5<pt(e)<5.5',30,0.,15.,0.)

      call hbook1(45550,'ntracks distribution e from D,
     &4.5<pt(e)<5.5',10,0.5,10.5,0.)
      call hbook1(45551,'sumpt distribution e from D,
     &4.5<pt(e)<5.5',30,0.,15.,0.)

      call hbook1(245550,'ntracks distribution Minbias,
     &4.5<pt(e)<5.5',10,0.5,10.5,0.)
      call hbook1(245551,'sumpt distribution Minbias,
     &4.5<pt(e)<5.5',30,0.,15.,0.)
c********************************************************
      call hbook2(525350,'ntracks VS from D',
     &20,0.5,20.5,21,-0.5,20.5,0.)
      call hbook2(525351,'sumpt All VS from D',
     &60,0.,30.,61,-0.5,30.,0.)
      call hbook2(535450,'ntracks VS from D',
     &20,0.5,20.5,21,-0.5,20.5,0.)
      call hbook2(535451,'sumpt All VS from D',
     &60,0.,30.,61,-0.5,30.,0.)
      call hbook2(545550,'ntracks VS from D',
     &20,0.5,20.5,21,-0.5,20.5,0.)
      call hbook2(545551,'sumpt All VS from D',
     &60,0.,30.,61,-0.5,30.,0.)

      call hbook2(625350,'ntracks VS from B',
     &20,0.5,20.5,21,-0.5,20.5,0.)
      call hbook2(625351,'sumpt All VS from B',
     &60,0.,30.,61,-0.5,30.,0.)
      call hbook2(635450,'ntracks VS from B',
     &20,0.5,20.5,21,-0.5,20.5,0.)
      call hbook2(635451,'sumpt All VS from B',
     &60,0.,30.,61,-0.5,30.,0.)
      call hbook2(645550,'ntracks VS from B',
     &20,0.5,20.5,21,-0.5,20.5,0.)
      call hbook2(645551,'sumpt All VS from B',
     &60,0.,30.,61,-0.5,30.,0.)
c********************************************************
      call hbook1(13545,'E parent B pt distribution,
     &3.5<pt(e)<4.5',60,0.,30.,0.)
      call hbook1(14555,'E parent B pt distribution,
     &4.5<pt(e)<5.5',60,0.,30.,0.)
      call hbook1(12535,'E parent B pt distribution,
     &2.5<pt(e)<3.5',60,0.,30.,0.)
      call hbook1(140,'E parent B pt distribution,
     &pt(e)>4.0',60,0.,30.,0.)
      call hbook1(150,'E parent B pt distribution,
     &pt(e)>5.0',60,0.,30.,0.)
      call hbook1(3545,'E parent D pt distribution,
     &3.5<pt(e)<4.5',60,0.,30.,0.)
      call hbook1(4555,'E parent D pt distribution,
     &4.5<pt(e)<5.5',60,0.,30.,0.)
      call hbook1(2535,'E parent D pt distribution,
     &2.5<pt(e)<3.5',60,0.,30.,0.)
      call hbook1(40,'E parent D pt distribution,
     &pt(e)>4.0',60,0.,30.,0.)
      call hbook1(50,'E parent D pt distribution,
     &pt(e)>5.0',60,0.,30.,0.)
      call hbook1(23545,'E parent MB pt distribution,
     &3.5<pt(e)<4.5',60,0.,30.,0.)
      call hbook1(24555,'E parent MB pt distribution,
     &4.5<pt(e)<5.5',60,0.,30.,0.)
      call hbook1(22535,'E parent MB pt distribution,
     &2.5<pt(e)<3.5',60,0.,30.,0.)
      call hbook1(240,'E parent MB pt distribution,
     &pt(e)>4.0',60,0.,30.,0.)
      call hbook1(250,'E parent MB pt distribution,
     &pt(e)>5.0',60,0.,30.,0.)
c**********************************************************************
      call hbook1(8,'delta eta distribution,no e cut D',240,
     &-12.0,12.0,0.)
      call hbook1(9,'delta phi distribution,no e cut D',126,
     &-6.3,6.3,0.)

      call hbook1(18,'delta eta distribution,no e cut B',240,
     &-12.0,12.0,0.)
      call hbook1(19,'delta phi distribution,no e cut B',126,
     &-6.3,6.3,0.)

      call hbook1(28,'delta eta distribution,no e cut MB',240,
     &-12.0,12.0,0.)
      call hbook1(29,'delta phi distribution,no e cut MB',126,
     &-6.3,6.3,0.)

      call hbook1(82535,'delta eta distribution,2.5<pt(e)<3.5 D',
     &240,-12.0,12.0,0.)
      call hbook1(92535,'delta phi distribution,2.5<pt(e)<3.5 D',
     &126,-6.3,6.3,0.)

      call hbook1(182535,'delta eta distribution,2.5<pt(e)<3.5 B',
     &240,-12.0,12.0,0.)
      call hbook1(192535,'delta phi distribution,2.5<pt(e)<3.5 B',
     &126,-6.3,6.3,0.)

      call hbook1(282535,'delta eta distribution,2.5<pt(e)<3.5 MB',
     &240,-12.0,12.0,0.)
      call hbook1(292535,'delta phi distribution,2.5<pt(e)<3.5 MB',
     &126,-6.3,6.3,0.)

      call hbook1(83545,'delta eta distribution,3.5<pt(e)<4.5 D',
     &240,-12.0,12.0,0.)
      call hbook1(93545,'delta phi distribution,3.5<pt(e)<4.5 D',
     &126,-6.3,6.3,0.)

      call hbook1(183545,'delta eta distribution,3.5<pt(e)<4.5 B',
     &240,-12.0,12.0,0.)
      call hbook1(193545,'delta phi distribution,3.5<pt(e)<4.5 B',
     &126,-6.3,6.3,0.)

      call hbook1(283545,'delta eta distribution,3.5<pt(e)<4.5 MB',
     &240,-12.0,12.0,0.)
      call hbook1(293545,'delta phi distribution,3.5<pt(e)<4.5 MB',
     &126,-6.3,6.3,0.)

      call hbook1(84555,'delta eta distribution,4.5<pt(e)<5.5 D',
     &240,-12.0,12.0,0.)
      call hbook1(94555,'delta phi distribution,4.5<pt(e)<5.5 D',
     &126,-6.3,6.3,0.)

      call hbook1(184555,'delta eta distribution,4.5<pt(e)<5.5 B',
     &240,-12.0,12.0,0.)
      call hbook1(194555,'delta phi distribution,4.5<pt(e)<5.5 B',
     &126,-6.3,6.3,0.)

      call hbook1(284555,'delta eta distribution,4.5<pt(e)<5.5 MB',
     &240,-12.0,12.0,0.)
      call hbook1(294555,'delta phi distribution,4.5<pt(e)<5.5 MB',
     &126,-6.3,6.3,0.)

      call hbook1(3,'electron phi distribution D',126,-6.3,6.3,0.)
      call hbook1(13,'electron phi distribution B',126,-6.3,6.3,0.)
      call hbook1(23,'electron phi distribution MB',126,-6.3,6.3,0.)

      call hbook1(4,'e pt distribution D',160,0.,16.,0.)
      call hbook1(14,'e pt distribution B',160,0.,16.,0.)
      call hbook1(24,'e pt distribution MB',160,0.,16.,0.)
c************************************************************
      call hbook2(999,' electron pt VS D pt',
     &160,0.,16.,160,0.,16.,0.)

      call hbook2(888,' electron pt VS B pt',
     &160,0.,16.,160,0.,16.,0.)
c***************************************************************
      call hbook2(1981,'D elecpt VS all hadron pt ',
     &160,0.,16.,200,0.,20.,0.)
      call hbook2(1982,'D elecpt VS D hadron pt ',
     &160,0.,16.,200,0.,20.,0.)

      call hbook2(1983,'B elecpt VS all hadron pt ',
     &160,0.,16.,200,0.,20.,0.)
      call hbook2(1984,'B elecpt VS B hadron pt ',
     &160,0.,16.,200,0.,20.,0.)

      call hbook2(1985,'D elecpt VS D hadron pt,same direction ',
     &160,0.,16.,200,0.,20.,0.)
      call hbook2(1986,'B elecpt VS B hadron pt,same direction ',
     &160,0.,16.,200,0.,20.,0.)
c*****************************************************************

      call hbook1(42535,'e pt 2.5-3.5 with hadron D',160,0.,16.,0.)
      call hbook1(142535,'e pt 2.5-3.5 with hadron B',160,0.,16.,0.)
      call hbook1(242535,'e pt 2.5-3.5 with hadron MB',160,0.,16.,0.)

      call hbook1(43545,'e pt 3.5-4.5 with hadron D',160,0.,16.,0.)
      call hbook1(143545,'e pt 3.5-4.5 with hadron B',160,0.,16.,0.)
      call hbook1(243545,'e pt 3.5-4.5 with hadron MB',160,0.,16.,0.)

      call hbook1(44555,'e pt 4.5-5.5 with hadron D',160,0.,16.,0.)
      call hbook1(144555,'e pt 4.5-5.5 with hadron B',160,0.,16.,0.)
      call hbook1(244555,'e pt 4.5-5.5 with hadron MB',160,0.,16.,0.)
c*******************************************************************
      call hbook2(1000,' e-h delt phi VS electron pt for D',
     &160,0.,16.,126,-6.3,6.3,0.)
      call hbook2(2000,' e-h delt phi VS electron pt for B',
     &160,0.,16.,126,-6.3,6.3,0.)
      call hbook2(3000,' e-h delt phi VS electron pt for MB',
     &160,0.,16.,126,-6.3,6.3,0.)
c**********************************************************************
      call hbook2(10000,' e-D->h delt phi VS electron pt for D',
     &160,0.,16.,126,-6.3,6.3,0.)
      call hbook2(20000,' e-B->h delt phi VS electron pt for B',
     &160,0.,16.,126,-6.3,6.3,0.)
      call hbook2(30000,' e-D/B->h delt phi VS electron pt for MB',
     &160,0.,16.,126,-6.3,6.3,0.)
C*************************************************************************

c        CKIN(1)=20.0      ! sqrt(s) min 
c        CKIN(3)=10.0
        MSEL=1
        MRPY(1)=77
c       MRPY(1)=44910

       call hbnt(ntbase+1,'CW Ntupled','D')
       call hbnt(ntbase+2,'CW Ntupleb','D')
       call hbnt(ntbase+3,'CW Ntuplemb','D')

c      write (name_string,100)
c      call hbname(ntbase+1,'General',mult,name_string)

      write (name_string,100) MAX_TRACKS
      call hbname(ntbase+1,'Trackd',tracksd,name_string)

      write (name_string,200) MAX_TRACKS
      call hbname(ntbase+2,'Trackb',tracksb,name_string)

      write (name_string,400) MAX_TRACKS
      call hbname(ntbase+3,'Trackmb',tracksmb,name_string)

        MSTU(11)=34
       open(mstu(11),file='minbias0.out',
     &  status='unknown')
        ndump=100000
c        neve=20000000
        neve=10
c***********************************************bylxy
c       print*,'Please input number of event'
c       read(*,*) neve
c***********************************************        
        i=0
c*************tuned pythia parameters****************
         parp(91)=1.5 ! inital pt width of a gaussian dist. D=1.0, 2.5
         parp(93)=10. ! maximum allowed pt from the initial broadening D=5.0,10
         pmas(4,1)=1.25 ! mass_c D=1.5
c         pmas(5,1)=4.8 ! mass_b D=4.8
         parp(31)=3.5 ! K factor, D=1.5 
         mstp(33)=1 ! using K factor D=0, no K factor
         mstp(32)=4 !  defination of Q^2 D=8
         mstp(51)=7 !  CTEQ5L
         parp(67)=4 ! factor multiplied to Q^2
c         parp(71)=8             ! factor multiplied to Q^2
         MSTJ(11)=3 ! peterson function is used for c and heavier
         parj(54)=-0.00001 
         parj(55)=-0.00001
c         MSTJ(44)=3 ! pt is used for alpha scaling
c        CKIN(3)= pmas(4,1)
c        CKIN(3)=5.0
c        CKin(5)=CKIN(3)
c*******************open charm ID **********************************************

c         MDCY(LUCOMP(421),1) = 0 ! D0,D0bar
c         MDCY(LUCOMP(423),1) = 0 ! D0*,D0bar*
c         MDCY(LUCOMP(413),1) = 0 ! D*+-
c         MDCY(LUCOMP(411),1) = 0 ! D+-
c         MDCY(LUCOMP(431),1) = 0 ! Ds+-
c         MDCY(LUCOMP(433),1) = 0 ! Ds*+-
c         MDCY(LUCOMP(511),1) = 0 ! B0,D0bar
c         MDCY(LUCOMP(513),1) = 0 ! B0*,D0bar*
c         MDCY(LUCOMP(523),1) = 0 ! B*+-
c         MDCY(LUCOMP(521),1) = 0 ! B+-
c         MDCY(LUCOMP(531),1) = 0 ! Bs+-
c         MDCY(LUCOMP(533),1) = 0 ! Bs*+-
c**************************************************************************
        IFILE1=11 
        OPEN(IFILE1,NAME='minbias0.dat',
     &   STATUS='UNKNOWN')
        call pyinit('cms','p','p',200D0)
       call pystat(2)
        nchtotal=0
        nbb=0 ! number of bbar pairs
        ncc=0 ! number of ccbar pairs
        nde=0 ! number of high pt elec from D events
        nbe=0 ! number of high pt elec from B events

        neventd025=0
        neventd03=0
        neventd035=0
        neventd04=0

        neventb025=0
        neventb03=0
        neventb035=0
        neventb04=0

        ntracksd025=0
        ntracksd03=0
        ntracksd035=0
        ntracksd04=0

        ntracksb025=0
        ntracksb03=0
        ntracksb035=0
	ntracksb1035=0
        ntracksb04=0

250     i=i+1
c####################################################
c       if(mod(i,500000).eq.10) print*,'***** ',i
c#####################################################
 300    call pyevnt

455     IF(I.EQ.1) THEN
        do L=1,50
        KPA(L)=0          
        MM(L)=0
        enddo
        ENDIF
        iphid=0
	iphib=0
	iphimb=0
        icc=0
        ibb=0
        DO 43 J=1,N    
           if(abs(k(j,2)).eq.4.and.icc.eq.0)then
              icc=1
              ncc=ncc+1
           elseif(abs(k(j,2)).eq.5.and.ibb.eq.0)then
              ibb=1
              nbb=nbb+1
           endif

c******************************store needed particles (open charms and electrons)*********************
      if((abs(k(j,2)).eq.11.and.(abs(k(k(j,3),2)).eq.411.or.
     &abs(k(k(j,3),2)).eq.421.or.abs(k(k(j,3),2)).eq.431)).and.
     &abs(pyp(j,19)).lt.0.7) then
	sumptd2535=0.0
	ntrad2535=0

	sumptd3545=0.0
        ntrad3545=0

	sumptd4555=0.0
        ntrad4555=0

        sumptdfra2535=0.0
        ntradfra2535=0

        sumptdfra3545=0.0
        ntradfra3545=0

        sumptdfra4555=0.0
        ntradfra4555=0

        elecptd=pyp(j,10)
        parentptd=pyp(k(j,3),10)
        elecetad=pyp(j,19)
        elecphid=pyp(j,15)

	elecpxd=pyp(j,1)
	elecpyd=pyp(j,2)
	elecpzd=pyp(j,3)
	elecpd=pyp(j,8)

	call hfill(3,elecphid,0.,1.)
	call hfill(4,elecptd,0.,1.)
	call hfill(999,elecptd,parentptd,1.)
        if(elecptd.gt.2.5.and.elecptd.lt.3.5)then
                call hfill(2535,parentptd,0.,1.)
        endif
        if(elecptd.gt.3.5.and.elecptd.lt.4.5)then
                call hfill(3545,parentptd,0.,1.)
        endif
        if(elecptd.gt.4.5.and.elecptd.lt.5.5)then
                call hfill(4555,parentptd,0.,1.)
        endif
        if(elecptd.gt.4.0)then
                call hfill(40,parentptd,0.,1.)
        endif
        if(elecptd.gt.5.0)then
                call hfill(50,parentptd,0.,1.)
        endif

	do jj=1,N
           if((abs(k(jj,2)).eq.211.or.abs(k(jj,2)).eq.321.or.
     &abs(k(jj,2)).eq.2212).and.abs(pyp(jj,19)).lt.1.05.and.
     &pyp(jj,10).ge.0.1)then
	      detad=pyp(jj,19)-elecetad
	      dphid=pyp(jj,15)-elecphid
              dphi2d=dphid
              if(dphid.gt.3.14159275)then
                 dphi2d=dphid-2*Pi
              endif
              if(dphid.lt.-3.14159275)then
                 dphi2d=dphid+2*Pi
              endif

	      call hfill(8,detad,0.,1.)
	      call hfill(9,dphi2d,0.,1.)
	      if(elecptd.lt.3.5.and.elecptd.gt.2.5)then
                 call hfill(82535,detad,0.,1.)
                 call hfill(92535,dphi2d,0.,1.)
              endif
              if(elecptd.lt.4.5.and.elecptd.gt.3.5)then
                 call hfill(83545,detad,0.,1.)
                 call hfill(93545,dphi2d,0.,1.)
              endif
              if(elecptd.lt.5.5.and.elecptd.gt.4.5)then
                 call hfill(84555,detad,0.,1.)
                 call hfill(94555,dphi2d,0.,1.)
              endif
	      if(elecptd.gt.2.0)then
		call hfill(1000,elecptd,dphi2d,1.)
	      endif

              if(elecptd.gt.2.0)then
		allhadptd=pyp(jj,10)
		call hfill(1981,elecptd,allhadptd,1.)
	      endif

c*************************************************
	      if(elecptd.gt.2.0)then
		iphid=iphid+1
		tmpvaluesd(iphid,1)=elecptd
		tmpvaluesd(iphid,2)=pyp(jj,10)
		tmpvaluesd(iphid,3)=dphi2d
		tmpvaluesd(iphid,4)=888.0
		tmpvaluesd(iphid,5)=888.0
	      endif

c*****************************************************
	      if(abs(dphi2d).lt.0.35.and.abs(detad).lt.0.35)then
		if(elecptd.lt.3.5.and.elecptd.gt.2.5)then
		  ntrad2535=ntrad2535+1
		  sumptd2535=sumptd2535+pyp(jj,10)
		endif
		if(elecptd.lt.4.5.and.elecptd.gt.3.5)then
                  ntrad3545=ntrad3545+1
                  sumptd3545=sumptd3545+pyp(jj,10)
                endif
                if(elecptd.lt.5.5.and.elecptd.gt.4.5)then
                  ntrad4555=ntrad4555+1
                  sumptd4555=sumptd4555+pyp(jj,10)
                endif
	      endif

	   endif
c***********************************************************************
        if((abs(k(jj,2)).eq.211.and.(abs(k(k(jj,3),2)).eq.411.or.
     &abs(k(k(jj,3),2)).eq.421.or.abs(k(k(jj,3),2)).eq.431.or.
     &abs(k(k(k(jj,3),3),2)).eq.411.or.abs(k(k(k(jj,3),3),2)).eq.421.or.
     &abs(k(k(k(jj,3),3),2)).eq.431.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.411.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.421.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.431)).or.
     &(abs(k(jj,2)).eq.321.and.(abs(k(k(jj,3),2)).eq.411.or.
     &abs(k(k(jj,3),2)).eq.421.or.abs(k(k(jj,3),2)).eq.431.or.
     &abs(k(k(k(jj,3),3),2)).eq.411.or.abs(k(k(k(jj,3),3),2)).eq.421.or.
     &abs(k(k(k(jj,3),3),2)).eq.431.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.411.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.421.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.431)).or.
     &(abs(k(jj,2)).eq.2212.and.(abs(k(k(jj,3),2)).eq.411.or.
     &abs(k(k(jj,3),2)).eq.421.or.abs(k(k(jj,3),2)).eq.431.or.
     &abs(k(k(k(jj,3),3),2)).eq.411.or.abs(k(k(k(jj,3),3),2)).eq.421.or.
     &abs(k(k(k(jj,3),3),2)).eq.431.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.411.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.421.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.431))) then
          if(abs(pyp(jj,19)).lt.1.05.and.pyp(jj,10).ge.0.1) then
                detadfra=pyp(jj,19)-elecetad
                dphidfra=pyp(jj,15)-elecphid
		dphi2dfra=dphidfra
                if(dphidfra.gt.3.14159275)then
                   dphi2dfra=dphidfra-2*Pi
                endif
                if(dphidfra.lt.-3.14159275)then
                   dphi2dfra=dphidfra+2*Pi
                endif
              if(elecptd.gt.2.0)then
                call hfill(10000,elecptd,dphi2dfra,1.)
              endif
c*****************************************************
	      if(elecptd.gt.2.0)then
		tmpvaluesd(iphid,4)=pyp(jj,10)
                tmpvaluesd(iphid,5)=dphi2dfra
	      endif
c******************************************************
              if(elecptd.gt.2.0)then
                dhadptd=pyp(jj,10)
                call hfill(1982,elecptd,dhadptd,1.)
                hadronpxd=pyp(jj,1)
                hadronpyd=pyp(jj,2)
                hadronpzd=pyp(jj,3)
                hadronpd=pyp(jj,8)
		cosvalued=(elecpxd*hadronpxd+elecpyd*hadronpyd+
     &elecpzd*hadronpzd)/(elecpd*hadronpd)
		thetad=acos(cosvalued)

		if(thetad.gt.-Pi/2.0.and.thetad.lt.Pi/2.0)then
		  call hfill(1985,elecptd,dhadptd,1.)
		endif
		
              endif

	  endif

          if(abs(dphi2dfra).lt.0.35.and.abs(detadfra).lt.0.35)then
              if(elecptd.lt.3.5.and.elecptd.gt.2.5)then
                ntradfra2535=ntradfra2535+1
                sumptdfra2535=sumptdfra2535+pyp(jj,10)
              endif
              if(elecptd.lt.4.5.and.elecptd.gt.3.5)then
                ntradfra3545=ntradfra3545+1
                sumptdfra3545=sumptdfra3545+pyp(jj,10)
              endif
              if(elecptd.lt.5.5.and.elecptd.gt.4.5)then
                ntradfra4555=ntradfra4555+1
                sumptdfra4555=sumptdfra4555+pyp(jj,10)
              endif
           endif

	endif
c**************************************************************************

	enddo

	if(ntrad2535.gt.0) then
           trad2535=ntrad2535
           call hfill(25350,trad2535,0.,1.)
           call hfill(25351,sumptd2535,0.,1.)
	   call hfill(42535,elecptd,0.,1.)

	   if(ntradfra2535.eq.0) then
	      sumptdfra2535=-0.2
	   endif
	   tradfra2535=ntradfra2535
	   call hfill(525350,trad2535,tradfra2535,1.)
	   call hfill(525351,sumptd2535,sumptdfra2535,1.)
        endif

	if(ntrad3545.gt.0) then
           trad3545=ntrad3545
           call hfill(35450,trad3545,0.,1.)
           call hfill(35451,sumptd3545,0.,1.)
	   call hfill(43545,elecptd,0.,1.)

           if(ntradfra3545.eq.0) then
              sumptdfra3545=-0.2
           endif
           tradfra3545=ntradfra3545
           call hfill(535450,trad3545,tradfra3545,1.)
           call hfill(535451,sumptd3545,sumptdfra3545,1.)
        endif

	if(ntrad4555.gt.0) then
           trad4555=ntrad4555
           call hfill(45550,trad4555,0.,1.)
           call hfill(45551,sumptd4555,0.,1.)
	   call hfill(44555,elecptd,0.,1.)

           if(ntradfra4555.eq.0) then
              sumptdfra4555=-0.2
           endif
           tradfra4555=ntradfra4555
           call hfill(545550,trad4555,tradfra4555,1.)
           call hfill(545551,sumptd4555,sumptdfra4555,1.)
        endif

      endif

      if((abs(k(j,2)).eq.11.and.(abs(k(k(j,3),2)).eq.511.or.
     &abs(k(k(j,3),2)).eq.521.or.abs(k(k(j,3),2)).eq.531)).and.
     &abs(pyp(j,19)).lt.0.7) then
	sumptb2535=0.0
        ntrab2535=0

        sumptb3545=0.0
        ntrab3545=0

        sumptb4555=0.0
        ntrab4555=0

        sumptbfra2535=0.0
        ntrabfra2535=0

        sumptbfra3545=0.0
        ntrabfra3545=0

        sumptbfra4555=0.0
        ntrabfra4555=0

        elecptb=pyp(j,10)
        parentptb=pyp(k(j,3),10)
        elecetab=pyp(j,19)
        elecphib=pyp(j,15)

	elecpxb=pyp(j,1)
	elecpyb=pyp(j,2)
	elecpzb=pyp(j,3)
	elecpb=pyp(j,8)

        call hfill(13,elecphib,0.,1.)
        call hfill(14,elecptb,0.,1.)
	call hfill(888,elecptb,parentptb,1.)
        if(elecptb.gt.2.5.and.elecptb.lt.3.5)then
                call hfill(12535,parentptb,0.,1.)
        endif
        if(elecptb.gt.3.5.and.elecptb.lt.4.5)then
                call hfill(13545,parentptb,0.,1.)
        endif
        if(elecptb.gt.4.5.and.elecptb.lt.5.5)then
                call hfill(14555,parentptb,0.,1.)
        endif
	if(elecptb.gt.4.0)then
                call hfill(140,parentptb,0.,1.)
        endif
	if(elecptb.gt.5.0)then
                call hfill(150,parentptb,0.,1.)
        endif

	do jj=1,N
           if((abs(k(jj,2)).eq.211.or.abs(k(jj,2)).eq.321.or.
     &abs(k(jj,2)).eq.2212).and.abs(pyp(jj,19)).lt.1.05.and.
     &pyp(jj,10).ge.0.1)then
              detab=pyp(jj,19)-elecetab
              dphib=pyp(jj,15)-elecphib
              dphi2b=dphib
              if(dphib.gt.3.14159275)then
                 dphi2b=dphib-2*Pi
              endif
              if(dphib.lt.-3.14159275)then
                 dphi2b=dphib+2*Pi
              endif

              call hfill(18,detab,0.,1.)
              call hfill(19,dphi2b,0.,1.)
              if(elecptb.lt.3.5.and.elecptb.gt.2.5)then
                 call hfill(182535,detab,0.,1.)
                 call hfill(192535,dphi2b,0.,1.)
              endif
              if(elecptb.lt.4.5.and.elecptb.gt.3.5)then
                 call hfill(183545,detab,0.,1.)
                 call hfill(193545,dphi2b,0.,1.)
              endif
              if(elecptb.lt.5.5.and.elecptb.gt.4.5)then
                 call hfill(184555,detab,0.,1.)
                 call hfill(194555,dphi2b,0.,1.)
              endif
	      if(elecptb.gt.2.0)then
	         call hfill(2000,elecptb,dphi2b,1.)
	      endif

              if(elecptb.gt.2.0)then
		allhadptb=pyp(jj,10)
		call hfill(1983,elecptb,allhadptb,1.)
	      endif
c****************************************************
	      if(elecptb.gt.2.0)then
                iphib=iphib+1
                tmpvaluesb(iphib,1)=elecptb
                tmpvaluesb(iphib,2)=pyp(jj,10)
                tmpvaluesb(iphib,3)=dphi2b
		tmpvaluesb(iphib,4)=888.0
		tmpvaluesb(iphib,5)=888.0
              endif

c********************************************************

              if(abs(dphi2b).lt.0.35.and.abs(detab).lt.0.35)then
                if(elecptb.lt.3.5.and.elecptb.gt.2.5)then
                  ntrab2535=ntrab2535+1
                  sumptb2535=sumptb2535+pyp(jj,10)
                endif
                if(elecptb.lt.4.5.and.elecptb.gt.3.5)then
                  ntrab3545=ntrab3545+1
                  sumptb3545=sumptb3545+pyp(jj,10)
                endif
                if(elecptb.lt.5.5.and.elecptb.gt.4.5)then
                  ntrab4555=ntrab4555+1
                  sumptb4555=sumptb4555+pyp(jj,10)
                endif
              endif

	   endif
c****************************************************************
        if((abs(k(jj,2)).eq.211.and.(abs(k(k(jj,3),2)).eq.511.or.
     &abs(k(k(jj,3),2)).eq.521.or.abs(k(k(jj,3),2)).eq.531.or.
     &abs(k(k(k(jj,3),3),2)).eq.511.or.abs(k(k(k(jj,3),3),2)).eq.521.or.
     &abs(k(k(k(jj,3),3),2)).eq.531.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.511.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.521.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.531)).or.
     &(abs(k(jj,2)).eq.321.and.(abs(k(k(jj,3),2)).eq.511.or.
     &abs(k(k(jj,3),2)).eq.521.or.abs(k(k(jj,3),2)).eq.531.or.
     &abs(k(k(k(jj,3),3),2)).eq.511.or.abs(k(k(k(jj,3),3),2)).eq.521.or.
     &abs(k(k(k(jj,3),3),2)).eq.531.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.511.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.521.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.531)).or.
     &(abs(k(jj,2)).eq.2212.and.(abs(k(k(jj,3),2)).eq.511.or.
     &abs(k(k(jj,3),2)).eq.521.or.abs(k(k(jj,3),2)).eq.531.or.
     &abs(k(k(k(jj,3),3),2)).eq.511.or.abs(k(k(k(jj,3),3),2)).eq.521.or.
     &abs(k(k(k(jj,3),3),2)).eq.531.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.511.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.521.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.531))) then
          if(abs(pyp(jj,19)).lt.1.05.and.pyp(jj,10).ge.0.1) then
                detabfra=pyp(jj,19)-elecetab
                dphibfra=pyp(jj,15)-elecphib
		dphi2bfra=dphibfra
                if(dphibfra.gt.3.14159275)then
                   dphi2bfra=dphibfra-2*Pi
                endif
                if(dphibfra.lt.-3.14159275)then
                   dphi2bfra=dphibfra+2*Pi
                endif
              if(elecptb.gt.2.0)then
                 call hfill(20000,elecptb,dphi2bfra,1.)
              endif
c****************************************************
	      if(elecptb.gt.2.0)then
		tmpvaluesb(iphib,4)=pyp(jj,10)
                tmpvaluesb(iphib,5)=dphi2bfra
	      endif
c***************************************************
              if(elecptb.gt.2.0)then
                bhadptb=pyp(jj,10)
                call hfill(1984,elecptb,bhadptb,1.)
		hadronpxb=pyp(jj,1)
		hadronpyb=pyp(jj,2)
		hadronpzb=pyp(jj,3)
		hadronpb=pyp(jj,8)
		cosvalueb=(elecpxb*hadronpxb+elecpyb*hadronpyb+
     &elecpzb*hadronpzb)/(elecpb*hadronpb)
		thetab=acos(cosvalueb)
		if(thetab.gt.-Pi/2.0.and.thetab.lt.Pi/2.0)then
		  call hfill(1986,elecptb,bhadptb,1.)
		endif

              endif

          endif
          if(abs(dphi2bfra).lt.0.35.and.abs(detabfra).lt.0.35)then
              if(elecptb.lt.3.5.and.elecptb.gt.2.5)then
                ntrabfra2535=ntrabfra2535+1
                sumptbfra2535=sumptbfra2535+pyp(jj,10)
              endif
              if(elecptb.lt.4.5.and.elecptb.gt.3.5)then
                ntrabfra3545=ntrabfra3545+1
                sumptbfra3545=sumptbfra3545+pyp(jj,10)
              endif
              if(elecptb.lt.5.5.and.elecptb.gt.4.5)then
                ntrabfra4555=ntrabfra4555+1
                sumptbfra4555=sumptbfra4555+pyp(jj,10)
              endif
          endif

	endif
c*****************************************************************************
	enddo

        if(ntrab2535.gt.0) then
           trab2535=ntrab2535
           call hfill(125350,trab2535,0.,1.)
           call hfill(125351,sumptb2535,0.,1.)
	   call hfill(142535,elecptb,0.,1.)

	   if(ntrabfra2535.eq.0) then
	     sumptbfra2535=-0.2
	   endif
	   trabfra2535=ntrabfra2535
	   call hfill(625350,trab2535,trabfra2535,1.)
	   call hfill(625351,sumptb2535,sumptbfra2535,1.)
        endif

        if(ntrab3545.gt.0) then
           trab3545=ntrab3545
           call hfill(135450,trab3545,0.,1.)
           call hfill(135451,sumptb3545,0.,1.)
	   call hfill(143545,elecptb,0.,1.)


           if(ntrabfra3545.eq.0) then
             sumptbfra3545=-0.2
           endif
           trabfra3545=ntrabfra3545
           call hfill(635450,trab3545,trabfra3545,1.)
           call hfill(635451,sumptb3545,sumptbfra3545,1.)
        endif

        if(ntrab4555.gt.0) then
           trab4555=ntrab4555
           call hfill(145550,trab4555,0.,1.)
           call hfill(145551,sumptb4555,0.,1.)
           call hfill(144555,elecptb,0.,1.)

           if(ntrabfra4555.eq.0) then
             sumptbfra4555=-0.2
           endif
           trabfra4555=ntrabfra4555
           call hfill(645550,trab4555,trabfra4555,1.)
           call hfill(645551,sumptb4555,sumptbfra4555,1.)
        endif

      endif

      if((abs(k(j,2)).eq.11.and.(abs(k(k(j,3),2)).eq.511.or.
     &abs(k(k(j,3),2)).eq.521.or.abs(k(k(j,3),2)).eq.531.or.
     &abs(k(k(j,3),2)).eq.411.or.abs(k(k(j,3),2)).eq.421.or.
     &abs(k(k(j,3),2)).eq.431)).and.abs(pyp(j,19)).lt.0.7) then
        sumptm2535=0
        ntram2535=0

        sumptm3545=0
        ntram3545=0

        sumptm4555=0
        ntram4555=0

           elecptm=pyp(j,10)
	   parentptm=pyp(k(j,3),10)
           elecetam=pyp(j,19)
           elecphim=pyp(j,15)
     
	   call hfill(24,elecptm,0.,1.)
	   call hfill(23,elecphim,0.,1.)
           if(elecptm.gt.3.5.and.elecptm.lt.4.5)then 
                call hfill(23545,parentptm,0.,1.)
           endif
           if(elecptm.gt.4.5.and.elecptm.lt.5.5)then 
                call hfill(24555,parentptm,0.,1.)
           endif
           if(elecptm.gt.2.5.and.elecptm.lt.3.5)then
                call hfill(22535,parentptm,0.,1.)
           endif 
           if(elecptm.gt.4.0)then
                call hfill(240,parentptm,0.,1.)
           endif
           if(elecptm.gt.5.0)then
                call hfill(250,parentptm,0.,1.)
           endif

           do jj=1,N
              if((abs(k(jj,2)).eq.211.or.abs(k(jj,2)).eq.321.or.
     &abs(k(jj,2)).eq.2212).and.abs(pyp(jj,19)).lt.1.05.and.
     &pyp(jj,10).ge.0.1)then
                 detam=pyp(jj,19)-elecetam
                 dphim=pyp(jj,15)-elecphim
		 dphi2m=dphim
		if(dphim.gt.3.14159275)then 
			dphi2m=dphim-2*Pi
		endif
                if(dphim.lt.-3.14159275)then 
			dphi2m=dphim+2*Pi
		endif

		call hfill(28,detam,0.,1.)
                call hfill(29,dphi2m,0.,1.)
		if(elecptm.lt.3.5.and.elecptm.gt.2.5)then
			call hfill(282535,detam,0.,1.)
                        call hfill(292535,dphi2m,0.,1.)
                endif
		if(elecptm.lt.4.5.and.elecptm.gt.3.5)then
			call hfill(283545,detam,0.,1.)
                        call hfill(293545,dphi2m,0.,1.)
                endif
		if(elecptm.lt.5.5.and.elecptm.gt.4.5)then
			call hfill(284555,detam,0.,1.)
                        call hfill(294555,dphi2m,0.,1.)
                endif
		if(elecptm.gt.2.0)then
			call hfill(3000,elecptm,dphi2m,1.)
		endif
c**************************************************************
	      if(elecptm.gt.2.0)then
                iphimb=iphimb+1
                tmpvaluesmb(iphimb,1)=elecptm
                tmpvaluesmb(iphimb,2)=pyp(jj,10)
                tmpvaluesmb(iphimb,3)=dphi2m
              endif

c****************************************************************
                if(abs(dphi2m).lt.0.35.and.abs(detam).lt.0.35)then
                    if(elecptm.lt.3.5.and.elecptm.gt.2.5)then
                          ntram2535=ntram2535+1
                          sumptm2535=sumptm2535+pyp(jj,10)
                    endif
                    if(elecptm.lt.4.5.and.elecptm.gt.3.5)then
                          ntram3545=ntram3545+1
                          sumptm3545=sumptm3545+pyp(jj,10)
                    endif
                    if(elecptm.lt.5.5.and.elecptm.gt.4.5)then
                          ntram4555=ntram4555+1
                          sumptm4555=sumptm4555+pyp(jj,10)
                    endif


                endif
                  
              endif
c***************************************************************
        if((abs(k(jj,2)).eq.211.and.(abs(k(k(jj,3),2)).eq.411.or.
     &abs(k(k(jj,3),2)).eq.421.or.abs(k(k(jj,3),2)).eq.431.or.
     &abs(k(k(jj,3),2)).eq.511.or.
     &abs(k(k(jj,3),2)).eq.521.or.abs(k(k(jj,3),2)).eq.531.or.
     &abs(k(k(k(jj,3),3),2)).eq.411.or.abs(k(k(k(jj,3),3),2)).eq.421.or.
     &abs(k(k(k(jj,3),3),2)).eq.431.or.
     &abs(k(k(k(jj,3),3),2)).eq.511.or.abs(k(k(k(jj,3),3),2)).eq.521.or.
     &abs(k(k(k(jj,3),3),2)).eq.531.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.411.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.421.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.431.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.511.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.521.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.531)).or.
     &(abs(k(jj,2)).eq.321.and.(abs(k(k(jj,3),2)).eq.411.or.
     &abs(k(k(jj,3),2)).eq.421.or.abs(k(k(jj,3),2)).eq.431.or.
     &abs(k(k(jj,3),2)).eq.511.or.
     &abs(k(k(jj,3),2)).eq.521.or.abs(k(k(jj,3),2)).eq.531.or.
     &abs(k(k(k(jj,3),3),2)).eq.411.or.abs(k(k(k(jj,3),3),2)).eq.421.or.
     &abs(k(k(k(jj,3),3),2)).eq.431.or.
     &abs(k(k(k(jj,3),3),2)).eq.511.or.abs(k(k(k(jj,3),3),2)).eq.521.or.
     &abs(k(k(k(jj,3),3),2)).eq.531.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.411.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.421.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.431.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.511.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.521.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.531)).or.
     &(abs(k(jj,2)).eq.2212.and.(abs(k(k(jj,3),2)).eq.411.or.
     &abs(k(k(jj,3),2)).eq.421.or.abs(k(k(jj,3),2)).eq.431.or.
     &abs(k(k(jj,3),2)).eq.511.or.
     &abs(k(k(jj,3),2)).eq.521.or.abs(k(k(jj,3),2)).eq.531.or.
     &abs(k(k(k(jj,3),3),2)).eq.411.or.abs(k(k(k(jj,3),3),2)).eq.421.or.
     &abs(k(k(k(jj,3),3),2)).eq.431.or.
     &abs(k(k(k(jj,3),3),2)).eq.511.or.abs(k(k(k(jj,3),3),2)).eq.521.or.
     &abs(k(k(k(jj,3),3),2)).eq.531.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.411.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.421.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.431.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.511.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.521.or.
     &abs(k(k(k(k(jj,3),3),3),2)).eq.531))) then
          if(abs(pyp(jj,19)).lt.1.05.and.pyp(jj,10).ge.0.1) then
                 detamfra=pyp(jj,19)-elecetam
                 dphimfra=pyp(jj,15)-elecphim
                 dphi2mfra=dphimfra
                if(dphimfra.gt.3.14159275)then
                        dphi2mfra=dphimfra-2*Pi
                endif
                if(dphimfra.lt.-3.14159275)then
                        dphi2mfra=dphimfra+2*Pi
                endif
                if(elecptm.gt.2.0)then
                        call hfill(30000,elecptm,dphi2mfra,1.)
                endif
	  endif

      endif



       enddo       

        if(ntram2535.gt.0) then
           tram2535=ntram2535
           call hfill(225350,tram2535,0.,1.)
           call hfill(225351,sumptm2535,0.,1.)
	   call hfill(242535,elecptm,0.,1.)
        endif

        if(ntram3545.gt.0) then
           tram3545=ntram3545
           call hfill(235450,tram3545,0.,1.)
           call hfill(235451,sumptm3545,0.,1.)
           call hfill(243545,elecptm,0.,1.)
        endif

        if(ntram4555.gt.0) then
           tram4555=ntram4555
           call hfill(245550,tram4555,0.,1.)
           call hfill(245551,sumptm4555,0.,1.)
	   call hfill(244555,elecptm,0.,1.)
        endif

      endif
 43     continue

c        if(iphi.ne.0.and.i.lt.60)call pylist(1)

        nchar=0 ! charge multiplicity in an event
        nhn=0 ! negatively charged multiplicity in an event
       
c        CALL LUEDIT(3)
          DO 44 J=1,N    
        if(pyp(j,6).ne.0.and.abs(pyp(j,19)).
     &  lt.0.5.and.k(j,1).le.10)nchar=nchar+1
        if(pyp(j,6).lt.0.and.abs(pyp(j,19)).
     &  lt.0.5.and.k(j,1).le.10)nhn=nhn+1
 44     continue
        mult=nchar
        hneg=nhn
        nevent=i
        nchtotal=nchtotal+nchar
c********************************************
	ijkd=0
	ijkb=0
	ijkmb=0

	if(iphid.ne.0)then
	  do 45 j=1,iphid
	    ijkd=ijkd+1
	    elecptd4nt(j)=tmpvaluesd(j,1)
            hadronptd4nt(j)=tmpvaluesd(j,2)
	    dphid4nt(j)=tmpvaluesd(j,3)
            d_hadronptd4nt(j)=tmpvaluesd(j,4)
            d_dphid4nt(j)=tmpvaluesd(j,5)
 45       continue
	endif	  
	    
	tracksd=ijkd
	if(tracksd.ge.1)then
	  call hfntb(3001,'Trackd')
	endif
	
        if(iphib.ne.0)then
          do 46 j=1,iphib
            ijkb=ijkb+1
            elecptb4nt(j)=tmpvaluesb(j,1)
            hadronptb4nt(j)=tmpvaluesb(j,2)
            dphib4nt(j)=tmpvaluesb(j,3)
            b_hadronptb4nt(j)=tmpvaluesb(j,4)
            b_dphib4nt(j)=tmpvaluesb(j,5)
 46       continue
        endif

        tracksb=ijkb
        if(tracksb.ge.1)then
          call hfntb(3002,'Trackb')
        endif

        if(iphimb.ne.0)then
          do 47 j=1,iphimb
            ijkmb=ijkmb+1
            elecptmb4nt(j)=tmpvaluesmb(j,1)
            hadronptmb4nt(j)=tmpvaluesmb(j,2)
            dphimb4nt(j)=tmpvaluesmb(j,3)
 47       continue
        endif

        tracksmb=ijkmb
        if(tracksmb.ge.1)then
          call hfntb(3003,'Trackmb')
        endif

  
        IF(mod(I,NDUMP).eq.0.or.i.eq.neve) THEN
c...........output some events after NDUMP-th events....................

        OPEN(IFILE1,NAME='minbias0.dat',
     &   STATUS='UNKNOWN')

        write(IFILE1,*)'event=',i,
     +'  mean charge multi=',nchtotal/real(i)
        write(IFILE1,*)'ccbarevent=',ncc,'  bbbarevent=',nbb
        write(IFILE1,*)'nde=',nde,' nbe=',nbe
c       write(IFILE1,*)'neventb035=',neventb035,
c     &' ntracksb035=',ntracksb035
        CLOSE(IFILE1)

        ENDIF
c***************************************************************
c        print*,'MRPY(2)=',MRPY(2),'  MRPY(3)=',MRPY(3),'  i=',i
c***************************************************************
        IF(I.LT.NEVE) GOTO 250                      
c********************************************
c...............fill ntuple after all events are finished
        CALL HROUT(0,ICYCLE,' ')
        CALL HREND('EXAM')
        call pystat(1)
540     close(mstu(11))

 100  format ( 'tracksd[0,',I3,']:I,',
     >         'elecptd4nt(tracksd):R,',
     >         'hadronptd4nt(tracksd):R,',
     >         'dphid4nt(tracksd):R,',
     >         'd_hadronptd4nt(tracksd):R,',
     >         'd_dphid4nt(tracksd):R')

 200  format ( 'tracksb[0,',I3,']:I,',
     >         'elecptb4nt(tracksb):R,',
     >         'hadronptb4nt(tracksb):R,',
     >         'dphib4nt(tracksb):R,',
     >         'b_hadronptb4nt(tracksb):R,',
     >         'b_dphib4nt(tracksb):R')

 400  format ( 'tracksmb[0,',I3,']:I,',
     >         'elecptmb4nt(tracksmb):R,',
     >         'hadronptmb4nt(tracksmb):R,',
     >         'dphimb4nt(tracksmb):R')

        STOP
        END 

