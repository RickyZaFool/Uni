{
	TRandom3 rnd;
	rnd.SetSeed(time(0));
	
	t = time(0);
	
	double N = 1000000000;
	double Nacc = 0;
	double r = 1;
	for (int i = 0; i < N; i++){
		double x = r*rnd.Rndm()*2-1;
		double y = r*rnd.Rndm()*2-1;
		double z = r*rnd.Rndm()*2-1;
		if ( sqrt(x*x+y*y) > r/2 && sqrt(x*x+y*y+z*z) < r){
			Nacc++;
		}
	}
	double p = Nacc / N;
	double ep  = sqrt(p*(1-p)/N);
	
	
	double Volume = p * 2*r*2*r*2*r;
	double eV = ep * 2*r*2*r*2*r;
	double ExpVolume = 4.0/3.0 * TMath::Pi() * r*r*r;
	cout << "Volume " << Volume << " pm " << eV << endl;
	cout << "SphereVolume " << ExpVolume << endl;
	t = time(0) - t;
	cout << " in " << t << " seconds " << endl;
}
