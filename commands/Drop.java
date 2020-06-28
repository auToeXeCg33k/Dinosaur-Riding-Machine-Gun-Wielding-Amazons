package commands;

import core.Data;
import core.Report;
import items.Item;

public class Drop implements Command {
  public Report execute(String[] strs, Data data) {
    if (data.getMaxMoves() == data.getMoves())
      return new Report("Nincs több lépésed.\n", false); 
    if (strs.length != 2)
      return new Report("Nem megfelelő a gyökérségek száma heló!\n", false); 
    if (((Select)data.getCommands().get("select")).getSelection() == null)
      return new Report("Válasszá ki valakit!\n", false); 
    if (((Select)data.getCommands().get("select")).getSelection().getHP() == 0.0D)
      return new Report(((Select)data.getCommands().get("select")).getSelection().getNev() + " nem is él.\n", false); 
    if (data.getItems().get(strs[1]) == null)
      return new Report("Olyen item, hogy " + strs[1] + ", nincs is!\n", false); 
    Item dropped = ((Select)data.getCommands().get("select")).getSelection().dropFromInventory((Class)data.getItems().get(strs[1]));
    if (dropped == null)
      return new Report(((Select)data.getCommands().get("select")).getSelection().getNev() + " amazonnál nincs " + ((Select)data.getCommands().get("select")).getSelection().getNev() + ".", false); 
    data.tileOfSelected().add(dropped);
    return new Report(strs[1] + "eldobva.\n" + strs[1], false);
  }
}
