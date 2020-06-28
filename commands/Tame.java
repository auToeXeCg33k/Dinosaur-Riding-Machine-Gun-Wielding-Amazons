package commands;

import core.Data;
import entities.Dinoszaurusz;

public class Tame implements Command {
  public String execute(String[] strs, Data data) {
    if (data.getMaxMoves() > data.getMoves()) {
      if (strs.length == 1) {
        if (((Select)data.getCommands().get("select")).getSelection() != null) {
          if (((Select)data.getCommands().get("select")).getSelection().getHP() > 0.0D) {
            if (((Select)data.getCommands().get("select")).getSelection().getDinoszaurusz() == null) {
              String ret;
              switch (data.tileOfSelected().getDinoszauruszList().size()) {
                case 0:
                  return "Nincs dinó a közelben.\n";
                case 1:
                  if (((Dinoszaurusz)data.tileOfSelected().getDinoszauruszList().get(0)).getTamed())
                    return "Ez a dinó mán másé.\n"; 
                  ((Select)data.getCommands().get("select")).getSelection().tame(data.tileOfSelected().getDinoszauruszList().get(0));
                  ret = "Dinó beidomítva.\n";
                  return ret.concat(data.nextMove());
              } 
              Dinoszaurusz temp = null;
              for (Dinoszaurusz dino : data.tileOfSelected().getDinoszauruszList()) {
                if (!dino.getTamed()) {
                  if (temp == null) {
                    temp = dino;
                    continue;
                  } 
                  if (dino.getHP() > temp.getHP())
                    temp = dino; 
                } 
              } 
              if (temp != null) {
                ((Select)data.getCommands().get("select")).getSelection().tame(temp);
                return "Dinó beidomítva.\n";
              } 
              return "Az összed dinó foglalt.\n";
            } 
            return ((Select)data.getCommands().get("select")).getSelection().getNev() + " amazonnak mán van dinója.\n";
          } 
          return "" + ((Select)data.getCommands().get("select")).getSelection() + " nem is él.\n";
        } 
        return "Válasszá ki valakit!\n";
      } 
      return "Nem megfelelő a gyökérségek száma heló!\n";
    } 
    return "Nincs több lépésed.\n";
  }
}
