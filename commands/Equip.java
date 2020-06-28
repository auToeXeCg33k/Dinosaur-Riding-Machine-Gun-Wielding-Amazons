package commands;

import core.Data;
import units.Report;

public class Equip implements Command {
  public Report execute(String[] strs, Data data) {
    if (strs.length != 2)
      return new Report("Nem megfelelő a gyökérségek száma heló!\n", false); 
    if (((Select)data.getCommands().get("select")).getSelection() == null)
      return new Report("Válasszá ki valakit!\n", false); 
    if (((Select)data.getCommands().get("select")).getSelection().getHP() == 0.0D)
      return new Report(((Select)data.getCommands().get("select")).getSelection().getNev() + " nem is él!\n", false); 
    if (data.getItems().get(strs[1]) == null)
      return new Report("Olyan fegyver, hogy " + strs[1] + ", nincs is!\n", false); 
    if (!((Select)data.getCommands().get("select")).getSelection().equip((Class)data.getItems().get(strs[1])))
      return new Report("Nincs is " + strs[1] + " az inventoryban!\n", false); 
    return new Report(strs[1] + " kézbe véve.\n", false);
  }
}
