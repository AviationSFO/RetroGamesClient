mkdir Platformer2000
cd Platformer2000
pip install gdown
gdown 1PiOAQytnLVXdBHXVyHF6dNBdnF-EzwQy

# expand Hello-Unity_Win64.zip 
Expand-Archive -LiteralPath Hello-Unity_Win64.Zip -DestinationPath ./

del Hello-Unity_Win64.Zip

echo "Download and install of Platformer 2000 complete"
