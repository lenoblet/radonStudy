{
	gSystem->Load("../../build/lib/libNEMO3Ana.so");
	//gROOT->ProcessLine(".x PlotStyle.C+");
	
	DataManagement::SetTotalRunTime            (86400*10);
	DataManagement::SetTotalAcceptedRunTime    (86400*10);
	DataManagement::SetTotalDeadTime           (0     );
		
	DataManagement::AddDataSet ( new DataSet ( "fake_data", 0, 0, 0));
	DataManagement::AddDataSet ( new DataSet ( "bulk"    ,  300000.0 ,  300000.0 ,  0 ));
	DataManagement::AddDataSet ( new DataSet ( "surface" ,  300000.0 ,  300000.0 ,  0 ));
	DataManagement::AddDataSet ( new DataSet ( "tracker" ,  300000.0 ,  300000.0 ,  0 ));

	// Load StudyRadon in StudyRadon
	HistoCollection * hcoll = new HistoCollection("StudyRadon", "StudyRadon");
	
	TFile * f = new TFile("../../histos/different_exposure/alpha_length_80.root");
	
	TDirectory * fdir = 0;
	TIter next(DataManagement::GetDataSetCollection()); DataSet * ds;	
	while( ds = (DataSet*) next() ){
		fdir = (TDirectory *) f->Get(ds->GetName()); fdir->cd();
		hcoll->Load(fdir);
	}
	
	//////////////////////////////////////////////////////////////////////////////
	//
	// Define the parameters
	//
	//////////////////////////////////////////////////////////////////////////////	
	DataManagement::AddParameter( new Parameter( "Bulk_Bi214"      , "Bulk_Bi214"      , 0 , 15.0*1e-3 , 0.1 ) );
	DataManagement::AddParameter( new Parameter( "Surface_Bi214"   , "Surface_Bi214"   , 1 , 1*1e-3 , 0.1 ) );
	DataManagement::AddParameter( new Parameter( "Tracker_Bi214"   , "Tracker_Bi214"   , 2 , 45.0*1e-3 , 0.1 ) );
	
	//////////////////////////////////////////////////////////////////////////////
	
	
	//////////////////////////////////////////////////////////////////////////////
	//
	// Define components
	//
	//////////////////////////////////////////////////////////////////////////////
	DataManagement::AddComponent( new Component("Bi214_Bulk",  "^{214}Bi Bulk",DataManagement::FindDataSet("bulk"),DataManagement::FindParameter("Bulk_Bi214"),1.0));
	DataManagement::FindComponent( "Bi214_Bulk" )->SetFillColor( kGray +1 );
                                                                                                                                                                                
	DataManagement::AddComponent( new Component("Bi214_Surface","^{214}Bi Surface",DataManagement::FindDataSet( "surface" ),DataManagement::FindParameter( "Surface_Bi214"),1.0)); 
	DataManagement::FindComponent( "Bi214_Surface")->SetFillColor( kAzure  +  1 );
                                                                                                                                                                                         
	DataManagement::AddComponent( new Component( "Bi214_Tracker","^{214}Bi Tracker",DataManagement::FindDataSet( "tracker" ),DataManagement::FindParameter( "Tracker_Bi214"),1.0));
	DataManagement::FindComponent( "Bi214_Tracker")->SetFillColor( kRed  -  7 );
	//////////////////////////////////////////////////////////////////////////////
	
	
	//////////////////////////////////////////////////////////////////////////////
	//	
	// Define the observables e_energy_P1_cold
	//
	//////////////////////////////////////////////////////////////////////////////
	Observable * alphaLength = new Observable("alphaLength", "1e1a - alpha track length " , kPhaseOne , hcoll->Find( "fake_data_AlphaTrackLength"   ) );
	alphaLength-> SetLogScale(kFALSE);
	//////////////////////////////////////////////////////////////////////////////
	
	
	//////////////////////////////////////////////////////////////////////////////
	//	
	// Add components to fit and the respective histogram
	//
	//////////////////////////////////////////////////////////////////////////////
	alphaLength -> AddComponent( DataManagement::FindComponent( "Bi214_Bulk"    ) , hcoll->Find( "bulk_AlphaTrackLength"      ) );		
	alphaLength -> AddComponent( DataManagement::FindComponent( "Bi214_Surface" ) , hcoll->Find( "surface_AlphaTrackLength"   ) );	
	alphaLength -> AddComponent( DataManagement::FindComponent( "Bi214_Tracker" ) , hcoll->Find( "tracker_AlphaTrackLength"   ) );
	//////////////////////////////////////////////////////////////////////////////
	

	//////////////////////////////////////////////////////////////////////////////
	//	
	// Add for fitting
	//
	//////////////////////////////////////////////////////////////////////////////
	DataManagement::FindParameter( "Bulk_Bi214"    ) ->Release();
	DataManagement::FindParameter( "Surface_Bi214" ) ->Release();
	DataManagement::FindParameter( "Tracker_Bi214" ) ->Release();
	DataManagement::AddObservable( alphaLength );
	//Fit::DoDrawScan();
	Fit::Run("Minuit", "Minimize");	
	

	alphaLength-> Draw(); 
	//(TPad*)gROOT->FindObject("alphaLength")   -> Print("StudyRadon.pdf");
	
	double value = DataManagement::FindParameter("Bulk_Bi214")->GetValInit();   //std::cout << value << std::endl;
	double error = DataManagement::FindParameter("Bulk_Bi214")->GetValError();  //std::cout << error << std::endl;
	double relative_error = error / value;                                      std::cout << "Relative error = "<< relative_error << std::endl;
}
