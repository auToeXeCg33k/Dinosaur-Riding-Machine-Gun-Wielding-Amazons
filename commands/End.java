package commands;

import core.Data;
import units.Report;
import entities.BrainDrainer;

public class End implements Command{

    @Override
    public Report execute(String[] strs, Data data) {
        for (int i = 0; i < data.getWorld().getSize(); i++)
            for (int j = 0; j < data.getWorld().getSize(); j++)
                if (data.getWorld().getTiles()[i][j].contains())
                {
                    java.util.Random random = new java.util.Random();
                    BrainDrainer temp = data.getWorld().getTiles()[i][j].remove();

                    while(true)
                    {
                        int temp1 = i + random.nextInt(2) - 1;
                        int temp2 = j + random.nextInt(2) - 1;

                        while (temp1 < 0 || temp1 >= data.getWorld().getSize())
                            temp1 = i + random.nextInt(2) - 1;

                        while (temp2 < 0 || temp2 >= data.getWorld().getSize())
                            temp2 = j + random.nextInt(2) - 1;

                        if (data.getWorld().getTiles()[temp1][temp2].add(temp))
                            break;
                    }
                }
        data.turn();
        return new Report("Player " + (data.getPlayerMarker() ? "2" : "1") + " parancsa:\n", true);
    }
}