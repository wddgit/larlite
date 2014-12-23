#ifndef SELECTIONTOOL_SPALGOEMPART_CXX
#define SELECTIONTOOL_SPALGOEMPART_CXX

#include "SPAlgoEMPart.h"

namespace sptool {

  SPAlgoEMPart::SPAlgoEMPart() 
    : SPAlgoBase()
    , _e_radLenPdf(nullptr)
    , _e_radLenData(nullptr)
    , _e_radLenVar(nullptr)
    , _e_radLenVal(nullptr)
    , _e_dEdxPdf(nullptr)
    , _e_dEdxData(nullptr)
    , _e_dEdxVar(nullptr)
    , _e_dEdxRange(nullptr)
    , _e_dEdxMu(nullptr)
    , _e_dEdxSigma(nullptr)
    , _g_radLenPdf(nullptr)
    , _g_radLenData(nullptr)
    , _g_radLenVar(nullptr)
    , _g_radLenVal(nullptr)
    , _g_dEdxPdf(nullptr)
    , _g_dEdxData(nullptr)
    , _g_dEdxVar(nullptr)
    , _g_dEdxRange(nullptr)
    , _g_dEdxMu(nullptr)
    , _g_dEdxSigma(nullptr)
  { 
    _name = "SPAlgoEMPart"; 
    Init();
  }

  void SPAlgoEMPart::Init()
  {
    _xmin = 0.;
    _xmax = 100.;
    _dedxmin = 0.;
    _dedxmax = 10.;
    _e_lval = -1000;
    _e_lmin = -10000;
    _e_lmax = -100;
    _e_dedxmu = 2.;
    _e_dedxsigma = _e_dedxmu*0.3;
    _e_dedxmin = _dedxmin;
    _e_dedxmax = _dedxmax;
    _g_lval = -1./20;
    _g_lmin = -1./10.;
    _g_lmax = -1./100.;
    _g_dedxmu = 4.;
    _g_dedxsigma = _g_dedxmu*0.3;
    _g_dedxmin = _dedxmin;
    _g_dedxmax = _dedxmax;
  }

  void SPAlgoEMPart::LoadParams(std::string fname,size_t version)
  {
    // Load user_info
    SPTBase::LoadParams(fname,version);
    // Extract if parameters found
    if(_params.exist_darray("rad_range")) {
      auto darray = _params.get_darray("rad_range");
      _xmin = (*darray)[0];
      _xmax = (*darray)[1];
      std::cout<<"["<<__FUNCTION__<<"]"
	       << " Loaded distance fit range : "
	       << _xmin << " => " << _xmax
	       << std::endl;
    }
    if(_params.exist_darray("dedx_range")) {
      auto darray = _params.get_darray("dedx_range");
      _dedxmin = (*darray)[0];
      _dedxmax = (*darray)[1];
      std::cout<<"["<<__FUNCTION__<<"]"
	       << " Loaded dEdx range : "
	       << _dedxmin << " => " << _dedxmax
		       << std::endl;
    }
    if(_params.exist_darray("gamma_params")) {
      auto darray = _params.get_darray("gamma_params");
      _g_lval = (*darray)[0];
      _g_lmin = (*darray)[1];
      _g_lmax = (*darray)[2];
      _g_dedxmu = (*darray)[3];
      _g_dedxsigma = (*darray)[4];
      std::cout<<"["<<__FUNCTION__<<"]"
	       <<" Loaded gamma parameters    : " << std::endl
	       <<"Rad Length: " << _g_lval << " ["<<_g_lmin<<" => "<<_g_lmax<<"]" << std:: endl
	       <<"dEdx: Mean: " << _g_dedxmu << " Sigma: " << _g_dedxsigma
	       <<std::endl;
    }
    if(_params.exist_darray("electron_params")) {
      auto darray = _params.get_darray("electron_params");
      _e_lval = (*darray)[0];
      _e_lmin = (*darray)[1];
      _e_lmax = (*darray)[2];
      _e_dedxmu = (*darray)[3];
      _e_dedxsigma = (*darray)[4];
      std::cout<<"["<<__FUNCTION__<<"]"
	       <<" Loaded electron parameters    : " << std::endl
	       <<"Rad Length: " << _e_lval << " ["<<_e_lmin<<" => "<<_e_lmax<<"]" << std:: endl
	       <<"dEdx: Mu:" << _e_dedxmu << " Sigma: "<<_e_dedxsigma
	       <<std::endl;
    }
  }

  void SPAlgoEMPart::Reset()
  {
    ShowerPdfFactory factory;
    std::string part_name = "gamma";
    if(!_mode) part_name = "electron";

    std::cout<<"electron: "<<_e_lval<<" : "<<_e_lmin<<" => "<<_e_lmax<<std::endl;
    // electron RadLen vars
    delete _e_radLenVal;
    _e_radLenVal   = new RooRealVar("_e_l","e Radiation length [cm]",_e_lval,_e_lmin,_e_lmax);
    delete _e_radLenVar;
    _e_radLenVar   = new RooRealVar("_e_rl","e Radiation length [cm]", _xmin, _xmax);
    // electron dEdx vars
    delete _e_dEdxRange;
    _e_dEdxRange = new RooRealVar("_e_dEdxRange","e dEdx [MeV]",_dedxmin,_dedxmax);
    delete _e_dEdxMu;
    _e_dEdxMu    = new RooRealVar("_e_dEdxMu","e dEdx Mean",_e_dedxmu,_e_dedxmin,_e_dedxmax);
    delete _e_dEdxSigma;
    _e_dEdxSigma = new RooRealVar("_e_dEdxSigma","e dEdx Sigma",_e_dedxsigma,0.,_e_dedxmax);
    delete _e_dEdxVar;
    _e_dEdxVar = new RooRealVar("_e_dEdx","e dEdx", _e_dedxmin, _e_dedxmax);
    delete _e_radLenPdf;
    _e_radLenPdf = factory.RadLenPdf(*_e_radLenVar, *_e_radLenVal);
    delete _e_radLenData;
    _e_radLenData = new RooDataSet(Form("%s_radLenData",part_name.c_str()),"RooFit distance data set",RooArgSet(*_e_radLenVar));
    delete _e_dEdxPdf;
    _e_dEdxPdf = factory.dEdxPdf(*_e_dEdxVar, *_e_dEdxMu, *_e_dEdxSigma);
    delete _e_dEdxData;
    _e_dEdxData = new RooDataSet(Form("%s_dEdxData",part_name.c_str()),"RooFit dEdx set",RooArgSet(*_e_dEdxVar));

    std::cout<<"gamma: "<<_g_lval<<" : "<<_g_lmin<<" => "<<_g_lmax<<std::endl;
    // gamma RadLen vars
    delete _g_radLenVal;
    _g_radLenVal   = new RooRealVar("_g_l","g Radiation length [cm]",_g_lval,_g_lmin,_g_lmax);
    delete _g_radLenVar;
    _g_radLenVar   = new RooRealVar("_g_rl","g Radiation length [cm]", _xmin, _xmax);
    // gamma dEdx vars
    delete _g_dEdxRange;
    _g_dEdxRange = new RooRealVar("_g_dEdxRange","g dEdx [MeV]",_dedxmin,_dedxmax);
    delete _g_dEdxMu;
    _g_dEdxMu    = new RooRealVar("_g_dEdxMu","g dEdx Mean",_g_dedxmu,_g_dedxmin,_g_dedxmax);
    delete _g_dEdxSigma;
    _g_dEdxSigma = new RooRealVar("_g_dEdxSigma","g dEdx Sigma",_g_dedxsigma,0.,_g_dedxmax);
    delete _g_dEdxVar;
    _g_dEdxVar = new RooRealVar("_g_dEdx","g dEdx", _g_dedxmin, _g_dedxmax);
    delete _g_radLenPdf;
    _g_radLenPdf = factory.RadLenPdf(*_g_radLenVar, *_g_radLenVal);
    delete _g_radLenData;
    _g_radLenData = new RooDataSet(Form("%s_radLenData",part_name.c_str()),"RooFit distance data set",RooArgSet(*_g_radLenVar));
    delete _g_dEdxPdf;
    _g_dEdxPdf = factory.dEdxPdf(*_g_dEdxVar, *_g_dEdxMu, *_g_dEdxSigma);
    delete _g_dEdxData;
    _g_dEdxData = new RooDataSet(Form("%s_dEdxData",part_name.c_str()),"RooFit dEdx set",RooArgSet(*_g_dEdxVar));

  }
  
  SPArticleSet SPAlgoEMPart::Select(const SPAData &data)
  {
    SPArticleSet res;
    if(!data._vtxs.size()) return res;

    for(auto const& s : data._showers) {

      double g_like = 0;
      double dist   = s.Start().Dist(data._vtxs[0]);

      if(dist > 1.){
	_g_radLenVar->setVal(dist);
	_e_radLenVar->setVal(dist);

	g_like = _g_radLenPdf->getVal(*_g_radLenVar) / ( _g_radLenPdf->getVal(*_g_radLenVar) + _e_radLenPdf->getVal(*_e_radLenVar) );
      }

      SPArticle p;
      if(g_like>0.5) p.pdg_code(22);
      else p.pdg_code(11);

      p.pos(s.Start());
      p.mom(s.Dir() * s._energy);
      p.energy(s._energy);
      
      res.push_back(p);
      /*
      std::cout<<_g_radLenVars[0].getVal()<< " ... " << g_like << " = ";
      if(g_like) std::cout<<"gamma"<<std::endl;
      else std::cout<<"electron"<<std::endl;
      */
    }
    
    return res;
  }

  void SPAlgoEMPart::Fill(const SPAData &data)
  {
    for ( auto &a : data._showers ){
      double x = a.Start().Dist(data._vtxs[0]);
      double dEdx = a._dedx;
      if(_mode) {
	_g_radLenVar->setVal(x);
	_g_dEdxVar->setVal(dEdx);
	_g_radLenData->add(RooArgSet(*_g_radLenVar));
	_g_dEdxData->add(RooArgSet(*_g_dEdxVar));
      }else{
	_e_radLenVar->setVal(x);
	_e_dEdxVar->setVal(dEdx);
	_e_radLenData->add(RooArgSet(*_e_radLenVar));
	_e_dEdxData->add(RooArgSet(*_e_dEdxVar));
      }
    }
  }

  void SPAlgoEMPart::ProcessEnd(TFile* fout)
  {

    RooPlot* frame_radLen = nullptr;
    RooPlot* frame_dEdx   = nullptr;
    RooFitResult* fit_res_radLen = nullptr;
    RooFitResult* fit_res_dEdx   = nullptr;
    std::string part_name = "gamma";
    if(!_mode) part_name = "electron";

    if(_mode) {
      fit_res_radLen = _g_radLenPdf->fitTo(*_g_radLenData,RooFit::Save());
      fit_res_radLen->Print();
      fit_res_dEdx   = _g_dEdxPdf->fitTo(*_g_dEdxData,RooFit::Save());
      fit_res_dEdx->Print();
      frame_radLen = _g_radLenVar->frame();
      frame_dEdx   = _g_dEdxVar->frame();
      _g_radLenData->plotOn(frame_radLen);
      _g_radLenPdf->plotOn(frame_radLen);
      _g_dEdxData->plotOn(frame_dEdx);
      _g_dEdxPdf->plotOn(frame_dEdx);
    }else{
      fit_res_radLen = _e_radLenPdf->fitTo(*_e_radLenData,RooFit::Save());
      fit_res_radLen->Print();
      fit_res_dEdx   = _e_dEdxPdf->fitTo(*_e_dEdxData,RooFit::Save());
      fit_res_dEdx->Print();
      frame_radLen = _e_radLenVar->frame();
      frame_dEdx   = _e_dEdxVar->frame();
      _e_radLenData->plotOn(frame_radLen);
      _e_radLenPdf->plotOn(frame_radLen);
      _e_dEdxData->plotOn(frame_dEdx);
      _e_dEdxPdf->plotOn(frame_dEdx);
    }

    if(_params.exist_darray(Form("%s_params",part_name.c_str()))) {
      std::cout<<"["<<__FUNCTION__<<Form("] Overwriting the stored param: %s_params",part_name.c_str())<<std::endl;
      _params.get_darray(Form("%s_params",part_name.c_str()))->clear();
    }

    RooRealVar* res_value_radLen = nullptr;
    RooRealVar* res_value_dEdxMu = nullptr;
    RooRealVar* res_value_dEdxSigma = nullptr;
    if(_mode){
      res_value_radLen = (RooRealVar*)(fit_res_radLen->floatParsFinal().find("_g_l"));
      res_value_dEdxMu   = (RooRealVar*)(fit_res_dEdx->floatParsFinal().find("_g_dEdxMu"));
      res_value_dEdxSigma   = (RooRealVar*)(fit_res_dEdx->floatParsFinal().find("_g_dEdxSigma"));
    }
    else{
      res_value_radLen = (RooRealVar*)(fit_res_radLen->floatParsFinal().find("_e_l"));
      res_value_dEdxMu   = (RooRealVar*)(fit_res_dEdx->floatParsFinal().find("_e_dEdxMu"));
      res_value_dEdxSigma   = (RooRealVar*)(fit_res_dEdx->floatParsFinal().find("_e_dEdxSigma"));
    }
    std::cout<<"["<<__FUNCTION__<<Form("] Storing new %s_params: ",part_name.c_str()) << std::endl
	     << "RadLen: "<< res_value_radLen->getVal() << " [" << res_value_radLen->getErrorLo()
	     << " => " << res_value_radLen->getErrorHi() << "]" << std::endl
	     << "dEdx: Mu: " << res_value_dEdxMu->getVal() << " Sigma: " << res_value_dEdxSigma << std::endl;
    _params.append(Form("%s_params",part_name.c_str()),res_value_radLen->getVal());
    _params.append(Form("%s_params",part_name.c_str()),res_value_radLen->getVal()+res_value_radLen->getErrorLo());
    _params.append(Form("%s_params",part_name.c_str()),res_value_radLen->getVal()+res_value_radLen->getErrorHi());
    _params.append(Form("%s_params",part_name.c_str()),res_value_dEdxMu->getVal());
    _params.append(Form("%s_params",part_name.c_str()),res_value_dEdxSigma->getVal());

    //_params.dump_contents();
    if(_params.exist_darray("rad_range"))
       _params.get_darray("rad_range")->clear();
    _params.append("rad_range",_xmin);
    _params.append("rad_range",_xmax);
    if(_params.exist_darray("dedx_range"))
       _params.get_darray("dedx_range")->clear();
    _params.append("dedx_range",_dedxmin);
    _params.append("dedx_range",_dedxmax);

    TCanvas *c = new TCanvas("c",Form("Distance PDF for %s",part_name.c_str()),1000,500);
    frame_radLen->Draw();
    c->SaveAs(Form("RadLength_%s.png",part_name.c_str()));
    delete c;
    c = new TCanvas("c",Form("dEdx PDF for %s",part_name.c_str()),1000,500);
    frame_dEdx->Draw();
    c->SaveAs(Form("dEdx_%s.png",part_name.c_str()));

    c->SetTitle("Selection Likelihood");

    TH1D *h11 = new TH1D("h11","Electron vs. Gamma Likelihood; Rad. Length [cm]; Likelihood",200,0,0.5);
    TH1D *h22 = new TH1D("h22","Electron vs. Gamma Likelihood; Rad. Length [cm]; Likelihood",200,0,0.5);

    for(size_t i=1; i<=100; ++i) {
      _e_radLenVar->setVal(0.5/200.*i);
      _g_radLenVar->setVal(0.5/200.*i);

      h11->SetBinContent(i,_e_radLenPdf->getVal(*_e_radLenVar) / (_e_radLenPdf->getVal(*_e_radLenVar) + _g_radLenPdf->getVal(*_g_radLenVar)));
      h22->SetBinContent(i,_g_radLenPdf->getVal(*_g_radLenVar) / (_e_radLenPdf->getVal(*_e_radLenVar) + _g_radLenPdf->getVal(*_g_radLenVar)));
    }

    h11->SetLineWidth(2);
    h11->SetLineColor(kBlue);
    h11->SetFillStyle(3004);
    h11->SetFillColor(kBlue);
    h22->SetLineWidth(2);
    h22->SetLineColor(kRed);
    h22->SetFillStyle(3003);
    h22->SetFillColor(kRed);

    h11->Draw();
    h22->Draw("sames");
    c->SaveAs("Likelihood.png");

    delete h11;
    delete h22;
    delete c;

  }

}

#endif