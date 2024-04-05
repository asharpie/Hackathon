import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Scanner;

import org.json.JSONArray;
import org.json.JSONObject;

    public class Driver {

        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter the name of a Pokémon: ");
            String pokemonName = scanner.nextLine();
            scanner.close();

            try {
                getPokemonCards(pokemonName);
            } catch (IOException e) {
                System.out.println("Error fetching Pokémon cards: " + e.getMessage());
            }
        }

        public static void getPokemonCards(String pokemonName) throws IOException {
            String url = "https://api.pokemontcg.io/v2/cards?q=name:" + pokemonName;

            URL apiUrl = new URL(url);
            HttpURLConnection connection = (HttpURLConnection) apiUrl.openConnection();
            connection.setRequestMethod("GET");
            connection.connect();

            int responseCode = connection.getResponseCode();
            if (responseCode == HttpURLConnection.HTTP_OK) {
                Scanner scanner = new Scanner(apiUrl.openStream());
                StringBuilder response = new StringBuilder();
                while (scanner.hasNext()) {
                    response.append(scanner.nextLine());
                }
                scanner.close();

                JSONObject jsonResponse = new JSONObject(response.toString());
                if (jsonResponse.has("data")) {
                    JSONArray cards = jsonResponse.getJSONArray("data");
                    for (int i = 0; i < cards.length(); i++) {
                        JSONObject card = cards.getJSONObject(i);
                        String cardName = card.getString("name");
                        String imageUrl = card.getJSONObject("images").getString("small");
                        System.out.println("Card Name: " + cardName);
                        System.out.println("Image URL: " + imageUrl);
                        System.out.println("-".repeat(50));
                    }
                } else {
                    System.out.println("No cards found for " + pokemonName);
                }
            } else {
                System.out.println("Failed to fetch Pokémon cards. HTTP error code: " + responseCode);
            }
            connection.disconnect();
        }
    }


