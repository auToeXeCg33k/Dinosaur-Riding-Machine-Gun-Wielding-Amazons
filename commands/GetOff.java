package commands;

import core.Data;

public class GetOff implements Command {
  public String execute(String[] strs, Data data) {
    if (strs.length == 1) {
      if (((Select)data.getCommand("select")).getSelection() != null) {
        if (((Select)data.getCommand("select")).getSelection().getHP() > 0.0D) {
          if (((Select)data.getCommand("select")).getSelection().getDinoszaurusz() != null) {
            if (((Select)data.getCommand("select")).getSelection().getDinoszaurusz().getHP() > 0.0D) {
              if (((Select)data.getCommand("select")).getSelection().isLovagol()) {
                data.tileOfSelected().addDinoszaurusz(((Select)data.getCommand("select")).getSelection().getDinoszaurusz());
                ((Select)data.getCommand("select")).getSelection().setLovagol(false);
                return ((Select)data.getCommand("select")).getSelection().getNev() + " leszállt a dinoszauruszról.\n";
              } 
              return ((Select)data.getCommand("select")).getSelection().getNev() + " nem is lovagol!\n";
            } 
            return ((Select)data.getCommand("select")).getSelection().getNev() + " dinoszaurusza nem él. Hullákról már nem nagyon lehet hogy leszállni dik...\n";
          } 
          return ((Select)data.getCommand("select")).getSelection().getNev() + " amazonnak nincs dinója. Idomíts be vele egyet!\n";
        } 
        return ((Select)data.getCommand("select")).getSelection().getNev() + " nem is él!\n";
      } 
      return "Válasszá ki valakit!\n";
    } 
    return "Nem megfelelő a gyökérségek száma heló!\n";
  }
}
