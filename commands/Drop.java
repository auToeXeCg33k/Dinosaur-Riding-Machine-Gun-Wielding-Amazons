package commands;

import core.Data;
import items.Item;

public class Drop implements Command {
  public String execute(String[] strs, Data data) {
    if (data.canDoAction()) {
      if (strs.length == 2) {
        if (((Select)data.getCommand("select")).getSelection() != null) {
          if (((Select)data.getCommand("select")).getSelection().getHP() > 0.0D) {
            if (data.getMaps().getItemClassMap().get(strs[1]) != null) {
              Item dropped = ((Select)data.getCommand("select")).getSelection().dropFromInventory((Class)data.getMaps().getItemClassMap().get(strs[1]));
              if (dropped != null) {
                data.tileOfSelected().addItem(dropped);
                return strs[1] + "eldobva.\n" + strs[1];
              } 
              return ((Select)data.getCommand("select")).getSelection().getNev() + " amazonnál nincs " + ((Select)data.getCommand("select")).getSelection().getNev() + ".";
            } 
            return "Olyen item, hogy " + strs[1] + ", nincs is!\n";
          } 
          return ((Select)data.getCommand("select")).getSelection().getNev() + " nem is él.\n";
        } 
        return "Válasszá ki valakit!\n";
      } 
      return "Nem megfelelő a gyökérségek száma heló!\n";
    } 
    return "Nincs több lépésed.\n";
  }
}
