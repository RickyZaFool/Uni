#include "squareGrid.h"
#include "gridPainter.h"
#include <TH2D.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>

gridPainter::gridPainter(const squareGrid& grid) : _grid(grid) {
    _canvas = new TCanvas("canvas", "Square Grid Canvas", 800, 600);
    _histogram = new TH2D("grid", " ", _grid.sideLenght(), 0, _grid.sideLenght(), _grid.sideLenght(), 0, _grid.sideLenght());
    gStyle->SetPalette(52);
    TColor::InvertPalette();
    _histogram->SetStats(0);
    _histogram->GetXaxis()->SetTickLength(-0.01);
    _histogram->GetYaxis()->SetTickLength(-0.01);
    legend = new TLegend(0.35,1,0.65,0.9);
}

void gridPainter::drawGrid() {
    int sideLength = _grid.sideLenght();
    for (int x = 0; x < sideLength; ++x) {
        for (int y = 0; y < sideLength; ++y) {
            if (_grid.isCellFilled(x, y)) {
                _histogram->SetBinContent(x + 1, y + 1, 1); // Set filled cells to 1
            } else {
                _histogram->SetBinContent(x + 1, y + 1, 0); // Set empty cells to 0
            }
        }
    }

    legend->Clear(); // Clear the legend before adding new entries
    legend->AddEntry((TObject*)nullptr, Form("Percentage Coverage: %.2f%%", _grid.percentageCoverage() * 100), "");
    legend->AddEntry((TObject*)nullptr, Form("Filled Cells: %d", _grid.filledCells()), "");
    _canvas->cd();    
    _histogram->Draw("COLZ, SAME"); // Draw the histogram with color
    legend->Draw();
    _canvas->Update(); // Update the canvas to reflect changes
}