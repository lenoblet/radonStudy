{
	gROOT->SetStyle("Plain");          
	gStyle->SetPalette(1);
	
	gStyle->SetHistLineWidth(1);
	
	gStyle->SetLabelFont(43,"XYZ");
	gStyle->SetLabelSize(15,"XYZ");
	gStyle->SetLabelOffset(0.01,"XYZ");
	
    gStyle->SetTitleFont(43,"XYZ");
    gStyle->SetTitleSize(15,"XYZ");
	gStyle->SetTitleOffset(2,"YZ");
	gStyle->SetTitleOffset(5,"X");

    //gStyle->SetTitleFont(43,"T");
    //gStyle->SetTitleSize(0.08,"T");	

    gStyle->SetPadGridX(true);
    gStyle->SetPadGridY(true);

	gStyle->SetLegendFillColor(kWhite);
	gStyle->SetLegendFont(43);
	gStyle->SetFillColor(kWhite);
	gStyle->SetTextFont(43);
	gStyle->SetTextSize(10);

    gROOT->ForceStyle();
	
}
