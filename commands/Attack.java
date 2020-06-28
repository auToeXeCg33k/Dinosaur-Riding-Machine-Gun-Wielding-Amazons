package commands;

import core.Data;

public class Attack implements Command {
  public String execute(String[] strs, Data data) {
    if (data.canDoAction()) {
      if (strs.length == 2) {
        if (((Select)data.getCommand("select")).getSelection() != null) {
          if (((Select)data.getCommand("select")).getSelection().getHP() != 0.0D) {
            if (((Select)data.getCommand("select")).getSelection().getGepFegyver() != null) {
              if (data.getOtherPlayer().hasAmazon(strs[1])) {
                if (data.tileOfSelected().containsAmazon(data.getOtherPlayer().getAmazon(strs[1]))) {
                  if (data.getOtherPlayer().getAmazon(strs[1]).getHP() != 0.0D) {
                    String ret = ((Select)data.getCommand("select")).getSelection().tamad(data.getOtherPlayer().getAmazon(strs[1])) + ((Select)data.getCommand("select")).getSelection().tamad(data.getOtherPlayer().getAmazon(strs[1]));
                    if (data.getOtherPlayer().getAmazon(strs[1]).getHP() == 0.0D)
                      data.getOtherPlayer().decActive(); 
                    return ret;
                  } 
                  return strs[1] + " is nem él.\n";
                } 
                return strs[1] + " nincs is rangeben.\n";
              } 
              return strs[1] + " nem is létezik.\n";
            } 
            return "Nem tok durrogtatni, fasse fogok.\n";
          } 
          return ((Select)data.getCommand("select")).getSelection().getNev() + " nem is él.\n";
        } 
        return "Válasszá valami buzit!\n";
      } 
      return "Nem megfelelő a gyökérségek száma heló!\n";
    } 
    return "Nincs több lépésed.\n";
  }
}
