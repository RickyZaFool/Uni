{
	TRandom3 rnd;
	rnd.SetSeed(2003050600);
	
	double d = 0.2;
	double l = 0.01;
	
	int N = 1000000;
	
	int Nacc = 0;
	int Nacc2 = 0;
	
	for (int i = 0; i < N; i++){
		double phi = rnd.Rndm() * 2 * TMath::Pi();
		double cthe = rnd.Rndm() * 2 - 1;
		double the = acos(cthe);
		if(the < TMath::Pi()/2){
			double alpha = d/cthe;
			double x = sin(the)*cos(phi)*alpha;
			double y = sin(the)*sin(phi)*alpha;
			if (abs(x) < (l/2) && abs(y) < (l/2)){
				Nacc ++;
			}
			if (abs(x-l/2) < (l/2) && abs(y-l/2) < (l/2)){
				Nacc2++;
			}
		}
	}
	double p = (double)Nacc/N;
	double p2 = (double)Nacc2/N;
	
	double ep = sqrt(p*(1-p)/N);
	double ep2 = sqrt(p2*(1-p2)/N); 
	
	cout << "Efficiency 1 " << p << "+/-" << ep << endl;
	cout << "Efficiency 2 " << p2 << "+/-" << ep2 << endl;
	
	double appr = l*l / (4*TMath::Pi()*d*d);
	
	cout << "Valore approssimato " << appr << endl;
}
