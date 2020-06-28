package commands;

import core.Data;

public class Move implements Command {
  public String execute(String[] strs, Data data) {
    if (data.canDoAction()) {
      if (strs.length == 3) {
        if (((Select)data.getCommand("select")).getSelection() != null) {
          if (((Select)data.getCommand("select")).getSelection().getHP() > 0.0D)
            for (int i = 0; i < (data.getWorld().getTiles()).length; i++) {
              for (int j = 0; j < (data.getWorld().getTiles()[0]).length; j++) {
                if (data.getWorld().getTiles()[i][j].containsAmazon(((Select)data.getCommand("select")).getSelection()))
                  try {
                    int temp1, temp2;
                    if (data.getPlayerMarker()) {
                      temp1 = data.getWorld().getSize().getY() - Integer.parseInt(strs[2]);
                      temp2 = data.getWorld().getSize().getX() - Integer.parseInt(strs[1]);
                    } else {
                      temp1 = Integer.parseInt(strs[2]) - 1;
                      temp2 = Integer.parseInt(strs[1]) - 1;
                    } 
                    if (temp1 >= data.getWorld().getSize().getX() || temp2 >= data.getWorld().getSize().getY() || temp1 < 0 || temp2 < 0)
                      return "Ilyen hely nincs is, a fasse tudja idetenni!\n"; 
                    if (temp1 == i && temp2 == j)
                      return "Mán ott vagy, fiam...\n"; 
                    if (temp1 > i + 1 || temp1 < i - 1 || temp2 > j + 1 || temp2 < j - 1)
                      return ((Select)data.getCommand("select")).getSelection().getNev() + " csak környező koordinátákra mehet!\n"; 
                    data.getWorld().getTiles()[i][j].rmAmazon(((Select)data.getCommand("select")).getSelection());
                    data.getWorld().getTiles()[temp1][temp2].addAmazon(((Select)data.getCommand("select")).getSelection());
                    String ret = "";
                    ret = ((Select)data.getCommand("select")).getSelection().getNev() + " elmozdult a(z) " + ((Select)data.getCommand("select")).getSelection().getNev() + ";" + strs[1] + " koordinátákra.\n";
                    ret = ret.concat(data.nextMove());
                    return ret;
                  } catch (NumberFormatException ex) {
                    return "Ezek nem is számok bazdmeg...\n";
                  }  
              } 
            }  
          return ((Select)data.getCommand("select")).getSelection().getNev() + " nem is él!\n";
        } 
        return "Válasszá ki valakit!\n";
      } 
      return "Nem megfelelő a gyökérségek száma heló!\n";
    } 
    return "Nincs több lépésed.\n";
  }
}
