Radon_on_source_foil() {

	/////////////////////////////////////////////////////////////////////////////
	/// Main ()                                                               /// 
	/////////////////////////////////////////////////////////////////////////////
	
	/// ***** Check before to launch the macro ***** ///
	/// *** the name of the input file 
	/// *** the name of the output file 
	/// *** the initial value of the fit 
	
	/// Introduce the pointer which not change during the macro     
	gSystem->Load("../../build/lib/libNEMO3Ana.so");
	gROOT->ProcessLine(".x PlotStyle.C+");
	
	TFile      * file = new TFile("../../histos/1e1a_events_source_selection/histo_alpha_length.root");
	
	TDirectory * directory_fake_data = (TDirectory*) file ->Get("fake_data");
	TH1F       * histo_tot           = (TH1F*) directory_fake_data  ->Get("fake_data_AlphaTrackLength");
	
	TDirectory * directory_bulk = (TDirectory*) file    ->Get("bulk");
	TH1F       * histo_bulk = (TH1F*) directory_bulk    ->Get("bulk_AlphaTrackLength");
	
	TDirectory * directory_surface = (TDirectory*) file ->Get("surface");
	TH1F       * histo_surf = (TH1F*) directory_surface ->Get("surface_AlphaTrackLength");
	
	TDirectory * directory_tracker = (TDirectory*) file ->Get("tracker");
	TH1F       * histo_trac = (TH1F*) directory_tracker ->Get("tracker_AlphaTrackLength");
	
	//system("reset_files.sh");
	ofstream file_bulk, file_surface, file_tracker;
	ofstream file_bulk_activity, file_surface_activity, file_tracker_activity;	
	
	/// Define the variables
	const Int_t expo_max = 110;
	int N_PE             = 100000;
	Int_t i_expo         = 0;
	std::vector<double> v_activity = 0;
		
	double r_bulk = 0;
	double r_surf = 0;
	double r_trac = 0;
		
	double r_bulk_error = 0;
	double r_surf_error = 0;
	double r_trac_error = 0;
	
	/// Prototype of the different functions
	TH1F * GenPseudoExp(int _exposure, TH1F* _histo);
	std::vector<double> Fit(int _exposure, TH1F* _histo_to_fit, TH1F* _histo_bulk, TH1F* _histo_surface, TH1F* _histo_tracker);
	
	/// Run  
  	for (i_expo = 80 ; i_expo < expo_max ; i_expo += 10 )  {
	
		v_activity = EvalExp(N_PE , i_expo, histo_tot, histo_bulk, histo_surf, histo_trac);
				
		r_bulk = (v_activity[2]/v_activity[0])  * 100;
		r_surf = (v_activity[6]/v_activity[4])  * 100;
		r_trac = (v_activity[10]/v_activity[8]) * 100;
		
		r_bulk_error = (v_activity[1]/v_activity[0] + v_activity[3]/v_activity[2])   * r_bulk;
		r_surf_error = (v_activity[5]/v_activity[4] + v_activity[7]/v_activity[6])   * r_surf;
		r_trac_error = (v_activity[9]/v_activity[8] + v_activity[11]/v_activity[10]) * r_trac;
		
		std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << r_trac << std::endl; 
		std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << v_activity[8] << std::endl; 
		
		///
		file_bulk.open("../../results/radon_on_source_foil/bulk_results.txt",ios_base::app);
		file_bulk << i_expo << " " << r_bulk << " " << r_bulk_error << endl;
  		file_bulk.close();
  		
  		file_bulk_activity.open("../../results/radon_on_source_foil/bulk_activity.txt",ios_base::app);
		file_bulk_activity << i_expo << " " << v_activity[0] << " " << v_activity[1] << endl;
  		file_bulk_activity.close();
  		
  		///
  		file_surface.open("../../results/radon_on_source_foil/surface_results.txt",ios_base::app);
		file_surface << i_expo << " " << r_surf << " " << r_surf_error << endl;
  		file_surface.close();
  		
  		file_surface_activity.open("../../results/radon_on_source_foil/surface_activity.txt",ios_base::app);
		file_surface_activity << i_expo << " " << v_activity[4] << " " << v_activity[5] << endl;
  		file_surface_activity.close();
  		
  		///
  		file_tracker.open("../../results/radon_on_source_foil/tracker_results.txt",ios_base::app);
		file_tracker << i_expo << " " << r_trac << " " << r_trac_error << endl;
  		file_tracker.close();
  		
  		file_tracker_activity.open("../../results/radon_on_source_foil/tracker_activity.txt",ios_base::app);
		file_tracker_activity << i_expo << " " << v_activity[8] << " " << v_activity[9] << endl;
  		file_tracker_activity.close();
	}
}



///////////////////////////////////////////////////////////////////////////////
/// Generate a pseudo experiment                                            ///
///////////////////////////////////////////////////////////////////////////////
TH1F * GenPseudoExp(int _exposure, TH1F* _histo) {
	
	double N_tot      = 0;
	double N_MC       = 0;
	TRandom3 * r      = new TRandom3();
	TH1F * _histo_new = new TH1F("histo new","histo new",50,0,500);
	_histo_new->Sumw2();
	
	N_tot = _histo->Integral() * _exposure;
	N_MC = r->Poisson(N_tot);
	_histo_new->FillRandom(_histo,int(N_MC));
	
	for (i = 0 ; i< _histo_new->GetNbinsX()+1 ; i++) {
	
		double N = _histo_new->GetBinContent(i);
		_histo_new->SetBinContent (i, N*1);
		_histo_new->SetBinError   (i, sqrt(N*1));
		
	}

	delete r;
	return _histo_new;
}
///////////////////////////////////////////////////////////////////////////////





///////////////////////////////////////////////////////////////////////////////
/// Fit 
///////////////////////////////////////////////////////////////////////////////
std::vector<double> Fit(int _exposure, TH1F* _histo_to_fit, TH1F* _histo_bulk, TH1F* _histo_surface, TH1F* _histo_tracker) {

	double value_bulk = 0;
	double value_surf = 0;
	double value_trac = 0;
		
	double error_bulk = 0;
	double error_surf = 0; 
	double error_trac = 0;

	DataManagement::AddDataSet ( new DataSet ( "fake_data", 0, 0, 0));	
	DataManagement::AddDataSet ( new DataSet ( "bulk"    ,  1000000.0 ,  1000000.0 ,  0 ));
	DataManagement::AddDataSet ( new DataSet ( "surface" ,  1000000.0 ,  1000000.0 ,  0 ));
	DataManagement::AddDataSet ( new DataSet ( "tracker" ,  1000000.0 ,  1000000.0 ,  0 ));
	
	DataManagement::AddParameter( new Parameter( "Bulk_Bi214"      , "Bulk_Bi214"      , 0 , 15.0e-3 , 0.1 ) ); 
	DataManagement::AddParameter( new Parameter( "Surface_Bi214"   , "Surface_Bi214"   , 1 , 0.20e-3, 0.1 ) ); 
	DataManagement::AddParameter( new Parameter( "Tracker_Bi214"   , "Tracker_Bi214"   , 2 , 45.5e-3 , 0.1 ) ); 
	
	DataManagement::AddComponent( new Component("Bi214_Bulk",  "^{214}Bi Bulk",DataManagement::FindDataSet("bulk"),DataManagement::FindParameter("Bulk_Bi214"),1.0));
	DataManagement::FindComponent( "Bi214_Bulk" )->SetFillColor( kGray +1 );
	DataManagement::AddComponent( new Component("Bi214_Surface","^{214}Bi Surface",DataManagement::FindDataSet( "surface" ),DataManagement::FindParameter( "Surface_Bi214"),1.0)); 
	DataManagement::FindComponent( "Bi214_Surface")->SetFillColor( kAzure  +  1 );
	DataManagement::AddComponent( new Component( "Bi214_Tracker","^{214}Bi Tracker",DataManagement::FindDataSet( "tracker" ),DataManagement::FindParameter( "Tracker_Bi214"),1.0));
	DataManagement::FindComponent( "Bi214_Tracker")->SetFillColor( kRed  -  7 );
	
	DataManagement::SetTotalRunTime            (86400);
	DataManagement::SetTotalAcceptedRunTime    (86400);
	DataManagement::SetTotalRunTime            (86400*_exposure);
	DataManagement::SetTotalAcceptedRunTime    (86400*_exposure);
	DataManagement::SetTotalDeadTime           (0     );
	
	//!
	//DataManagement::FindParameter( "Tracker_Bi214" )->SetFix();
	//DataManagement::FindParameter( "Surface_Bi214" )->IsLimited();
	//DataManagement::FindParameter( "Surface_Bi214" )->SetLimit(0,0.001);		
	Observable * alphaLength = new Observable("alphaLength", "1e1a - alpha track length" , kPhaseOne , _histo_to_fit );
	alphaLength-> SetLogScale(kFALSE);

	alphaLength -> AddComponent( DataManagement::FindComponent( "Bi214_Bulk"    ) , _histo_bulk    );		
	alphaLength -> AddComponent( DataManagement::FindComponent( "Bi214_Surface" ) , _histo_surface );	
	alphaLength -> AddComponent( DataManagement::FindComponent( "Bi214_Tracker" ) , _histo_tracker );

	DataManagement::AddObservable( alphaLength );
	Fit::Run("Minuit", "Minimize");	
	
	//alphaLength-> Draw(); 
	//(TPad*)gROOT->FindObject("alphaLength")   -> Print("StudyRadon.pdf");
	
	std::vector<double> v_activity_and_error = 0;
	 
	value_bulk = DataManagement::FindParameter("Bulk_Bi214")   ->GetValInit(); //std::cout << value << std::endl;
	value_surf = DataManagement::FindParameter("Surface_Bi214")->GetValInit(); //std::cout << value << std::endl;
	value_trac = DataManagement::FindParameter("Tracker_Bi214")->GetValInit(); //std::cout << value << std::endl;
		
	error_bulk = DataManagement::FindParameter("Bulk_Bi214")   ->GetValError();
	error_surf = DataManagement::FindParameter("Surface_Bi214")->GetValError(); 
	error_trac = DataManagement::FindParameter("Tracker_Bi214")->GetValError();
	
	// bulk value and error
	v_activity_and_error.push_back(value_bulk);
	v_activity_and_error.push_back(error_bulk);
	
	// surface value and error
	v_activity_and_error.push_back(value_surf);
	v_activity_and_error.push_back(error_surf);
	
	// tracker value and error
	v_activity_and_error.push_back(value_trac);
	v_activity_and_error.push_back(error_trac);
	
	DataManagement::GetObservableCollection() ->Clear();
	DataManagement::GetDataSetCollection()    ->Clear();
	DataManagement::GetParameterCollection()  ->Clear();
	DataManagement::GetComponentCollection()  ->Clear();
	delete alphaLength;
	return v_activity_and_error;	
}
/////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////////
/// EvalExp()                                                             ///
/////////////////////////////////////////////////////////////////////////////
std::vector<double> EvalExp(int _N_PE , int _exposure, TH1F * _histo_to_fit, TH1F* _histo_bulk, TH1F* _histo_surface, TH1F* _histo_tracker) {

	/*TH1F * h_bulk_activity = new TH1F("histo bulk","histo bulk",100,0.005,0.0250);
	TH1F * h_surf_activity = new TH1F("histo surf","histo surf",100,-0.0015,0.0015);
	TH1F * h_trac_activity = new TH1F("histo trac","histo trac",100,0.035,0.0550);*/
	
	TH1F * h_bulk_activity = new TH1F("histo bulk","histo bulk",100,-0.005,0.0250);
	TH1F * h_trac_activity = new TH1F("histo trac","histo trac",100,0.025,0.0650);
	TH1F * h_surf_activity = new TH1F("histo surf","histo surf",100,-0.0040,0.0040);
	
	std::vector<double> _activity_and_error = 0;
	double bulk_activity       =  0;
	double bulk_activity_error =  0;
	double surf_activity       =  0;
	double surf_activity_error =  0;
	double trac_activity       =  0;
	double trac_activity_error =  0;
		
	std::vector<double> _mean_activity_and_sigma_and_error = 0;
	double _mean_activity_bulk = 0;
	double _sigma_bulk         = 0;
	double _mean_activity_bulk_error = 0;
	double _sigma_bulk_error         = 0;
	
	double _mean_activity_surf = 0;
	double _sigma_surf         = 0;
	double _mean_activity_surf_error = 0;
	double _sigma_surf_error         = 0;
	
	double _mean_activity_trac = 0;
	double _sigma_trac         = 0;
	double _mean_activity_trac_error = 0;
	double _sigma_trac_error         = 0;
	
	
	for (i = 1 ; i <= _N_PE ; i ++) {
	
		TH1F * h_pseudo_exp = GenPseudoExp(_exposure, _histo_to_fit);
		_activity_and_error = Fit(_exposure , h_pseudo_exp , _histo_bulk , _histo_surface , _histo_tracker );
		
		double bulk_activity       = _activity_and_error[0];
		double bulk_activity_error = _activity_and_error[1];
	
		double surf_activity       = _activity_and_error[2];
		double surf_activity_error = _activity_and_error[3];
	
		double trac_activity       = _activity_and_error[4];
		double trac_activity_error = _activity_and_error[5];
	
		h_bulk_activity->Fill(_activity_and_error[0]);
		h_surf_activity->Fill(_activity_and_error[2]);
		h_trac_activity->Fill(_activity_and_error[4]);
		
		std::cout << "Bulk activity = " << bulk_activity << " +/- " << bulk_activity_error << std::endl;
		std::cout << "Surf activity = " << surf_activity << " +/- " << surf_activity_error << std::endl; 
		std::cout << "Trac activity = " << trac_activity << " +/- " << trac_activity_error << std::endl;
		
	}

	h_bulk_activity->Fit("gaus");
	_mean_activity_bulk       = gaus->GetParameter(1);
	_mean_activity_bulk_error = gaus->GetParError(1);
	_sigma_bulk               = gaus->GetParameter(2);
	_sigma_bulk_error         = gaus->GetParError(2);
	_mean_activity_and_sigma_and_error.push_back(_mean_activity_bulk);
	_mean_activity_and_sigma_and_error.push_back(_mean_activity_bulk_error);
	_mean_activity_and_sigma_and_error.push_back(_sigma_bulk);
	_mean_activity_and_sigma_and_error.push_back(_sigma_bulk_error);
	std::cout << "Mean activity bulk = " << _mean_activity_bulk << " , sigma = " << _sigma_bulk << std::endl;
	
	
	h_surf_activity->Fit("gaus");
	_mean_activity_surf       = gaus->GetParameter(1);
	_mean_activity_surf_error = gaus->GetParError(1);
	_sigma_surf               = gaus->GetParameter(2);
	_sigma_surf_error         = gaus->GetParError(2);
	_mean_activity_and_sigma_and_error.push_back(_mean_activity_surf); 
	_mean_activity_and_sigma_and_error.push_back(_mean_activity_surf_error);
	_mean_activity_and_sigma_and_error.push_back(_sigma_surf); 
	_mean_activity_and_sigma_and_error.push_back(_sigma_surf_error);
	std::cout << "Mean activity surf = " << _mean_activity_surf << " , sigma = " << _sigma_surf << std::endl;
	
	
	h_trac_activity->Fit("gaus");
	_mean_activity_tracker       = gaus->GetParameter(1);
	_mean_activity_tracker_error = gaus->GetParError(1);
	_sigma_tracker               = gaus->GetParameter(2);
	_sigma_tracker_error         = gaus->GetParError(2);
	_mean_activity_and_sigma_and_error.push_back(_mean_activity_tracker);
	_mean_activity_and_sigma_and_error.push_back(_mean_activity_tracker_error); 
	_mean_activity_and_sigma_and_error.push_back(_sigma_tracker);
	_mean_activity_and_sigma_and_error.push_back(_sigma_tracker_error); 
	std::cout << "Mean activity tracker = " << _mean_activity_tracker << " , sigma = " << _sigma_tracker << std::endl;
	
	
		
	delete h_pseudo_exp;	
	return _mean_activity_and_sigma_and_error;

}
/////////////////////////////////////////////////////////////////////////////

		
