
int FitAlphaTrackLength()  {

	gSystem->Load("../../build/lib/libNEMO3Ana.so");
	//gROOT->ProcessLine(".x PlotStyle.C+");
	
	TFile      * file = new TFile("../../histos/1e1a_events_source_selection/histo_alpha_length.root");
	
	TDirectory * directory_fake_data = (TDirectory*) file ->Get("fake_data");
	TH1F       * histo_tot           = (TH1F*) directory_fake_data  ->Get("fake_data_AlphaTrackLength");
	
	TDirectory * directory_bulk = (TDirectory*) file    ->Get("bulk");
	TH1F       * histo_bulk = (TH1F*) directory_bulk    ->Get("bulk_AlphaTrackLength");
	
	TDirectory * directory_surface = (TDirectory*) file ->Get("surface");
	TH1F       * histo_surf = (TH1F*) directory_surface ->Get("surface_AlphaTrackLength");
	
	TDirectory * directory_tracker = (TDirectory*) file ->Get("tracker");
	TH1F       * histo_trac = (TH1F*) directory_tracker ->Get("tracker_AlphaTrackLength");
	
		
	DataManagement::AddDataSet ( new DataSet ( "bulk"    ,  300000.0 ,  300000.0 ,  0 ));
	DataManagement::AddDataSet ( new DataSet ( "surface" ,  300000.0 ,  300000.0 ,  0 ));
	DataManagement::AddDataSet ( new DataSet ( "tracker" ,  300000.0 ,  300000.0 ,  0 ));
	
	DataManagement::AddParameter( new Parameter( "Bulk_Bi214"      , "Bulk_Bi214"      , 0 , 15.0e-3 , 0.1 ) ); 
	DataManagement::AddParameter( new Parameter( "Surface_Bi214"   , "Surface_Bi214"   , 1 , 1.0e-3, 0.1 ) ); 
	DataManagement::AddParameter( new Parameter( "Tracker_Bi214"   , "Tracker_Bi214"   , 2 , 45.5e-3 , 0.1 ) );
	
	DataManagement::AddComponent( new Component("Bi214_Bulk",  "^{214}Bi Bulk",DataManagement::FindDataSet("bulk"),DataManagement::FindParameter("Bulk_Bi214"),1.0));
	DataManagement::FindComponent( "Bi214_Bulk" )->SetFillColor( kGray +1 );
	DataManagement::AddComponent( new Component("Bi214_Surface","^{214}Bi Surface",DataManagement::FindDataSet( "surface" ),DataManagement::FindParameter( "Surface_Bi214"),1.0)); 
	DataManagement::FindComponent( "Bi214_Surface")->SetFillColor( kAzure  +  1 );
	DataManagement::AddComponent( new Component( "Bi214_Tracker","^{214}Bi Tracker",DataManagement::FindDataSet( "tracker" ),DataManagement::FindParameter( "Tracker_Bi214"),1.0));
	DataManagement::FindComponent( "Bi214_Tracker")->SetFillColor( kRed  -  7 );
	
	int exposure = 60;
	
	//DataManagement::SetTotalRunTime            (86400);
	//DataManagement::SetTotalAcceptedRunTime    (86400);
	DataManagement::SetTotalRunTime            (86400*exposure);
	DataManagement::SetTotalAcceptedRunTime    (86400*exposure);
	DataManagement::SetTotalDeadTime           (0     );
	
	//!
	//DataManagement::FindParameter( "Tracker_Bi214" )->SetFix();  		
	Observable * alphaLength = new Observable("alphaLength", "1e1a - alpha track length" , kPhaseOne , histo_tot);
	alphaLength-> SetLogScale(kFALSE);

	alphaLength -> AddComponent( DataManagement::FindComponent( "Bi214_Bulk"    ) , histo_bulk );		
	alphaLength -> AddComponent( DataManagement::FindComponent( "Bi214_Surface" ) , histo_surf );	
	alphaLength -> AddComponent( DataManagement::FindComponent( "Bi214_Tracker" ) , histo_trac );

	DataManagement::AddObservable( alphaLength );
	Fit::Run("Minuit", "Minimize");	
	
	alphaLength-> Draw();
	//histo_trac->Draw();
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
