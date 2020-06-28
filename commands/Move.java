package commands;

import core.Data;
import units.Point;
import units.Report;

public class Move implements Command {
  public Report execute(String[] strs, Data data) {
    if (data.getMaxMoves() == data.getMoves())
      return new Report("Nincs több lépésed.\n", false); 
    if (strs.length != 3)
      return new Report("Nem megfelelő a gyökérségek száma heló!\n", false); 
    if (((Select)data.getCommands().get("select")).getSelection() == null)
      return new Report("Válasszá ki valakit!\n", false); 
    if (((Select)data.getCommands().get("select")).getSelection().getHP() == 0.0D)
      return new Report(((Select)data.getCommands().get("select")).getSelection().getNev() + " nem is él!\n", false); 
    try {
      int temp1, temp2;
      if (data.getPlayerMarker()) {
        temp1 = data.getWorld().getSize() - Integer.parseInt(strs[2]);
        temp2 = data.getWorld().getSize() - Integer.parseInt(strs[1]);
      } else {
        temp1 = Integer.parseInt(strs[2]) - 1;
        temp2 = Integer.parseInt(strs[1]) - 1;
      } 
      if (temp1 >= data.getWorld().getSize() || temp2 >= data.getWorld().getSize() || temp1 < 0 || temp2 < 0)
        return new Report("Ilyen hely nincs is, a fasse tudja idetenni!\n", false); 
      Point p = data.location(((Select)data.getCommands().get("select")).getSelection());
      if (temp1 == p.getY() && temp2 == p.getX())
        return new Report("Mán ott vagy, fiam...\n", false); 
      if (temp1 > p.getY() + 1 || temp1 < p.getY() - 1 || temp2 > p.getX() + 1 || temp2 < p.getY() - 1)
        return new Report(((Select)data.getCommands().get("select")).getSelection().getNev() + " csak környező koordinátákra mehet!\n", false); 
      data.getWorld().getTiles()[p.getY()][p.getX()].remove(((Select)data.getCommands().get("select")).getSelection());
      data.getWorld().getTiles()[temp1][temp2].add(((Select)data.getCommands().get("select")).getSelection());
      String ret = "";
      ret = ((Select)data.getCommands().get("select")).getSelection().getNev() + " elmozdult a(z) " + ((Select)data.getCommands().get("select")).getSelection().getNev() + ";" + strs[1] + " koordinátákra.\n";
      if (data.getWorld().getTiles()[temp1][temp2].contains())
        ret = ret.concat(data.getWorld().getTiles()[temp1][temp2].getBrainDrainer().attack(((Select)data.getCommands().get("select")).getSelection())); 
      ret = ret.concat(data.nextMove());
      return new Report(ret, false);
    } catch (NumberFormatException ex) {
      return new Report("Ezek nem is számok bazdmeg...\n", false);
    } 
  }
}
