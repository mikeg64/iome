<<<<<<< .mine
#!/bin/bash
iogs initiome null mysim null >& /dev/null &

python uiexample2.py &

#dx -suppress -execute_on_change -program steerwave2d.net &

scilab -nb -nw -f steerwave.sce &
scilab -nb -nw -f vizwave.sce &



=======
#!/bin/bash
iogs initiome null mysim null >& /dev/null &

python uiexample2.py &

#dx -suppress -execute_on_change -program steerwave2d.net &

scilab -nb -nw -f steerwave.sce &

scilab -nb -f vizwave.sce


>>>>>>> .r362
