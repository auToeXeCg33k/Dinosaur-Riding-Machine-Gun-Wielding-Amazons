package commands;

import core.Data;
import core.Tile;
import entities.Dinoszaurusz;
import units.Point;
import units.Report;

public class Tame implements Command {
  public Report execute(String[] strs, Data data) {
    String ret;
    if (data.getMaxMoves() == data.getMoves())
      return new Report("Nincs több lépésed.\n", false); 
    if (strs.length != 1)
      return new Report("Nem megfelelő a gyökérségek száma heló!\n", false); 
    if (((Select)data.getCommands().get("select")).getSelection() == null)
      return new Report("Válasszá ki valakit!\n", false); 
    if (((Select)data.getCommands().get("select")).getSelection().getHP() == 0.0D)
      return new Report("" + ((Select)data.getCommands().get("select")).getSelection() + " nem is él.\n", false); 
    if (((Select)data.getCommands().get("select")).getSelection().getDinoszaurusz() != null)
      return new Report(((Select)data.getCommands().get("select")).getSelection().getNev() + " amazonnak mán van dinója.\n", false); 
    Point p = data.location(((Select)data.getCommands().get("select")).getSelection());
    Tile t = data.getWorld().getTiles()[p.getY()][p.getX()];
    switch (t.getDinoszauruszList().size()) {
      case 0:
        return new Report("Nincs dinó a közelben.\n", false);
      case 1:
        if (((Dinoszaurusz)t.getDinoszauruszList().get(0)).getTamed())
          return new Report("Ez a dinó mán másé.\n", false); 
        ((Select)data.getCommands().get("select")).getSelection().tame(t.getDinoszauruszList().get(0));
        ret = "Dinó beidomítva.\n";
        return new Report(ret.concat(data.nextMove()), false);
    } 
    Dinoszaurusz temp = null;
    for (Dinoszaurusz dino : t.getDinoszauruszList()) {
      if (!dino.getTamed()) {
        if (temp == null) {
          temp = dino;
          continue;
        } 
        if (dino.getHP() > temp.getHP())
          temp = dino; 
      } 
    } 
    if (temp == null)
      return new Report("Az összed dinó foglalt.\n", false); 
    ((Select)data.getCommands().get("select")).getSelection().tame(temp);
    return new Report("Dinó beidomítva.\n", false);
  }
}
