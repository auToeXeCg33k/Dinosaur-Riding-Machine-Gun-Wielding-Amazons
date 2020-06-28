package commands;

import core.Data;
import entities.BrainDrainer;
import java.util.Random;
import units.Report;

public class End implements Command {
  public Report execute(String[] strs, Data data) {
    for (int i = 0; i < data.getWorld().getSize(); i++) {
      for (int j = 0; j < data.getWorld().getSize(); j++) {
        if (data.getWorld().getTiles()[i][j].contains()) {
          int temp1, temp2;
          Random random = new Random();
          BrainDrainer temp = data.getWorld().getTiles()[i][j].remove();
          do {
            temp1 = i + random.nextInt(2) - 1;
            temp2 = j + random.nextInt(2) - 1;
            while (temp1 < 0 || temp1 >= data.getWorld().getSize())
              temp1 = i + random.nextInt(2) - 1; 
            while (temp2 < 0 || temp2 >= data.getWorld().getSize())
              temp2 = j + random.nextInt(2) - 1; 
          } while (!data.getWorld().getTiles()[temp1][temp2].add(temp));
        } 
      } 
    } 
    data.turn();
    return new Report("Player " + (data.getPlayerMarker() ? "2" : "1") + " parancsa:\n", true);
  }
}
