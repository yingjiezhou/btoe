int makedummy() {

   std::ofstream ofout("dummylist.list");
   int ntot = 9*20;
   for (int i=0;i<ntot;i++) ofout << i << std::endl;

   return 0;
}
