//
// Created by tim4ukys on 13.05.2023.
//
#include "main.hpp"

// FIXME:
// Кнопки в поле не реагируют на клик если зажать и отвезти курсор

int main() {
    sf::RenderWindow window{sf::VideoMode(512, 420), "Nonogram map creator", sf::Style::Titlebar | sf::Style::Close};
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);
    auto& io = ImGui::GetIO();
    io.MouseDrawCursor = true;
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("roboto.ttf", 13.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;
    ImGui::SFML::UpdateFontTexture();
    applyTheme();

    MapData mapData{};
    constexpr std::string_view OUT_FILE_NAME = "out_map.txt";
    if (std::filesystem::exists(OUT_FILE_NAME))
        mapData.loadDataFromFile(OUT_FILE_NAME);

    sf::Clock deltaClock{};
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("main_wnd", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);

        if (ImGui::Button(u8"Сохранить поле"))
            mapData.saveDataToFile("out_map.txt");

        if (ImGui::SliderInt(u8"Ширина и высота поля", &mapData.getLenData(), 2, 17))
            mapData.Create();

        if (ImGui::BeginTable(u8"Поле", mapData.getLenData(), ImGuiTableFlags_Borders | ImGuiTableFlags_NoSavedSettings))
        {
            for (int i{}; i < mapData.getLenData()*mapData.getLenData(); i++)
            {
                ImGui::TableNextColumn();
                ImGui::Selectable(("##" + std::to_string(i+1)).c_str(), &mapData[i]);
            }
            ImGui::EndTable();
        }

        ImGui::End();

        window.clear(sf::Color::Black);
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}
